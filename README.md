# Constraint Learning

## 1. Tutorial 중 Using the Articulation Model Library (C++) 사용해보기. 
---

### ***roslaunch articulation_tutorials model_fitting.launch***
---

* Model Fitting Library를 사용해보기 위해 내가 취득한 회전 작업에 대한 Demo를 사용함. 
* Demo data 중 Pose (x,y,z,qx,qy,qz,qw) 정보를 ModelMsg로 저장하였고, 이후 ModelMsg를 factory.restoreModel을 통해 C++ Object로 변환함. 
* factory.restoreModel을 통해 생성된 GenericModel 인스턴스는 fitModel, evaluateModel등의 메서드를 제공. 
* fitModel, evaluateModel을 통해 center of rotation, 그리고 model과 demo 사이 유사도인 log-likelihood를 확인할 수 있다. 
* **이 Tutorial의 경우에는 Rotation Model을 가정하고 Parameter만을 추정함.**
* **어떻게 Model을 추정하고, 그에 따른 Parameter를 추정하는지는 "articulation_models/model_learner_*.cpp"에서 확인해야 할 듯**


## 2. model_learner_msg.cpp 분석. 
---

### ***rosrun articulation_model model_learner_msg***
 - Run Model Fitting Node

### ***rosrun articulation_tutorials pose_generator.py***
 - Generate pose demo from .csv file
---

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

    * BIC 제일 작은걸 Model로 선정 후 이를 사용. 

    * Pose Generator Node를 활용해서 Prismatic, Rotational, Stationary Rotational Motion을 학습 한 결과, 모든 경우를 잘 구분하는 것을 확인할 수 있음. 

    * Model Parameter 확인 - rostopic echo /model/param을 통해 확인할 수 있음. 
        * rigid인 경우 rigid에 맞는 param, rot인 경우 rot에 맞는 param이 출력됨. 