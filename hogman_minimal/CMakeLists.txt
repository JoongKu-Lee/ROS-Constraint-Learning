cmake_minimum_required(VERSION 2.8.3)
project(hogman_minimal)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC") 

include_directories(include)

add_library(${PROJECT_NAME} SHARED
	src/csparse/cs_add.c
	src/csparse/cs_amd.c
	src/csparse/cs_chol.c
	src/csparse/cs_cholsol.c
	src/csparse/cs_compress.c
	src/csparse/cs_counts.c
	src/csparse/cs_cumsum.c
	src/csparse/cs_dfs.c
	src/csparse/cs_dmperm.c
	src/csparse/cs_droptol.c
	src/csparse/cs_dropzeros.c
	src/csparse/cs_dupl.c
	src/csparse/cs_entry.c
	src/csparse/cs_ereach.c
	src/csparse/cs_etree.c
	src/csparse/cs_fkeep.c
	src/csparse/cs_gaxpy.c
	src/csparse/cs_happly.c
	src/csparse/cs_house.c
	src/csparse/cs_ipvec.c
	src/csparse/cs_leaf.c
	src/csparse/cs_load.c
	src/csparse/cs_lsolve.c
	src/csparse/cs_ltsolve.c
	src/csparse/cs_lu.c
	src/csparse/cs_lusol.c
	src/csparse/cs_malloc.c
	src/csparse/cs_maxtrans.c
	src/csparse/cs_multiply.c
	src/csparse/cs_norm.c
	src/csparse/cs_permute.c
	src/csparse/cs_pinv.c
	src/csparse/cs_post.c
	src/csparse/cs_print.c
	src/csparse/cs_pvec.c
	src/csparse/cs_qr.c
	src/csparse/cs_qrsol.c
	src/csparse/cs_randperm.c
	src/csparse/cs_reach.c
	src/csparse/cs_scatter.c
	src/csparse/cs_scc.c
	src/csparse/cs_schol.c
	src/csparse/cs_spsolve.c
	src/csparse/cs_sqr.c
	src/csparse/cs_symperm.c
	src/csparse/cs_tdfs.c
	src/csparse/cs_transpose.c
	src/csparse/cs_updown.c
	src/csparse/cs_usolve.c
	src/csparse/cs_util.c
	src/csparse/cs_utsolve.c

	src/graph/graph.cpp
	src/graph/dijkstra.cpp
	src/graph/posegraph3d.cpp
	src/graph/loadEdges3d.cpp
	src/graph/posegraph2d.cpp

	src/graph_optimizer/graph_optimizer2d_aux.cpp

	src/graph_optimizer_hogman/csparse_helper.cpp
	src/graph_optimizer_hogman/graph_optimizer3d_chol.h
)


# rosbuild_add_executable(hogman2d
# 	src/graph_optimizer_hogman/hogman2d.cpp
# )

# rosbuild_add_executable(hogman3d
# 	src/graph_optimizer_hogman/hogman3d.cpp
# )
# target_link_libraries(hogman3d hogman_csparse hogman_stuff hogman_graph hogman_graph_optimizer hogman_graph_optimizer_hogman)
# target_link_libraries(hogman2d hogman_csparse hogman_stuff hogman_graph hogman_graph_optimizer hogman_graph_optimizer_hogman)
