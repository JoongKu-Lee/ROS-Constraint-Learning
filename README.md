# Constraint Learning

## 1. Tutorial 중 Using the Articulation Model Library (C++) 사용해보기. 

### ***roslaunch articulation_tutorials model_fitting.launch***

* Model Fitting Library를 사용해보기 위해 내가 취득한 회전 작업에 대한 Demo를 사용함. 
* Demo data 중 Pose (x,y,z,qx,qy,qz,qw) 정보를 ModelMsg로 저장하였고, 이후 ModelMsg를 factory.restoreModel을 통해 C++ Object로 변환함. 
* factory.restoreModel을 통해 생성된 GenericModel 인스턴스는 fitModel, evaluateModel등의 메서드를 제공. 
* fitModel, evaluateModel을 통해 center of rotation, 그리고 model과 demo 사이 유사도인 log-likelihood를 확인할 수 있다. 
* **이 Tutorial의 경우에는 Rotation Model을 가정하고 Parameter만을 추정함.**
* **어떻게 Model을 추정하고, 그에 따른 Parameter를 추정하는지는 "articulation_models/model_learner_*.cpp"에서 확인해야 할 듯**


## 2. model_learner_msg.cpp 분석. 

### ***rosrun articulation_model model_learner_msg***
 - Run Model Fitting Node

### ***rosrun articulation_tutorials pose_generator.py***
 - Generate pose demo from .csv file

* 일단 ParamMsg에도 종류가 있음. 

    * PRIOR : Model Fitting 전 설정된 prior parameter (sigma_position, sigma_orientation 등)
    * PARAM : Model Fitting 과정에서 max likelihood를 통해 찾은 Model Parameter (rot_radius 등)
    * EVAL : Model Fitting 이후 결과를 통해 찾은 Evaluation 결과 (BIC, loglikehood 등)

* Model Fitting 과정. 

    * Track 정보를 받으면, factory를 통해 새로운 모델 models_new 생성. 
    * 이전 모델은 models_old로 저장

    * 유일한 차이는 models_old는 setTrack을 하고, models_new는 fitModel을 수행. 
    * 뭔가 models_old는 이전에 설정된 model을 사용해 evaluate을 하고, models_new는 새로운 model을 설정해 evaluate를 하는 느낌인 듯....

    * Likelihood 계산법 : 각 Model Parameter로 추정한 결과값과 실제 결과값의 Error를 계산하고, 이 Error를 통해 MLESAC을 계산. 이 Likelihood 이용해 BIC 계산. 
        * 이거에 대해 좀 더 파헤쳐보자. 
        * 내가 생각하기엔, 각 Model(Rigid, Prismatic, Rotational)을 통해 주어진 PoseArray를 가장 잘 대변하는 Parameter(Prismatic인 경우 Origin/Direction, Rotation인 경우 Center/Radius)를 먼저 찾고, 그 Parameter를 통해 Predicted PoseArray를 만든 뒤 Predicted PoseArray와 Real PoseArray의 Cost를 통해 Best Model을 찾는걸로 생각됨. 
            * 이게 맞는지 확인해봅시다. 

        * `fitModel` 분석
          * sampleConsensus
          
              주어진 PoseArray에 대해 `guessParameters`를 정해진 `sac_iteration(100)`만큼 수행하고, 그 Parameter마다 LogLikelihood 계산 한 후 제일 큰 LogLikelihood가지는 놈으로 Parameter 변경. 
          
            * `guessParameters` : 각 Model마다 Parameter guess하는 함수 정의됨. 
              * Rigid: PoseArray로부터 임의의 Pose를 추출한 뒤 그 Pose의 Position/Orientation을 rigid position/orientation으로 저장. 
              * Prismatic: PoseArray로부터 임의의 두 Pose를 추출한 뒤 처음 임의의 Pose의 Position/Orientation을 rigid position/orientation으로 저장, Direction은 둘의 Position을 빼서 구함. 
              * Rotational: PoseArray로부터 임의의 세 Pose를 추출.이 세 Pose를 이용해 center, axis, radius, orientation을 구함.  
            * `getLogLikelihood` : 추정된 Parameter를 통해 Likelihood 계산. 
              * Inlier LogLikelihood와 Outlier LogLikelihood를 따로 계산함. 
              * `Inlier LogLikelihood` : 예측한 Pose와 실제 Pose 사이 차이를 통해 계산. 
                * 어떻게 예측하나? - predictConfiguration 이후 predictPose
                  * predictConfiguration : 현재 위치가 Model Parameter로 정해진 Constraint 상에서 어느정도의 Configuration에 위치해 있는지.. (e.g. Prismatic에서 시작점부터 어느정도 거리에 있는지)
                  * predictPose : predictConfiguration 결과를 Pose로 변환. 
                * 최종적으로, 예측한 Pose와 실제 Pose 차이를 LogLikelihood 식에 넣어서 계산. 

              * `Outlier LogLikelihood` : Outlier로 판단되었을 때의 LogLikelihood (chi-square 95%)

          * `optimizeParameters`
            * 계산된 Model Parameter들을 Optimize 함. 
            * Likelihood를 최대화 하도록 Parameter를 update함. Likelihood의 변화는 미미하나, 해주지 않는 것 보다는 좋은듯? 

          * `normalizeParameters`
            * 그냥 이전 Parameter와 방향이 심각하게 달라지거나 하는 걸 막아줌. 


        * `evaluateModel` 분석
          * BIC 계산. 

    * BIC 제일 작은걸 Model로 선정 후 이를 사용. 

    * Pose Generator Node를 활용해서 Prismatic, Rotational, Stationary Rotational Motion을 학습 한 결과, 모든 경우를 잘 구분하는 것을 확인할 수 있음. 

    * Model Parameter 확인 - rostopic echo /model/param을 통해 확인할 수 있음. 
        * rigid인 경우 rigid에 맞는 param, rot인 경우 rot에 맞는 param이 출력됨. 