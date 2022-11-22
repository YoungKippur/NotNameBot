# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "kamu_robotu_comm: 0 messages, 1 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(kamu_robotu_comm_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv" NAME_WE)
add_custom_target(_kamu_robotu_comm_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "kamu_robotu_comm" "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(kamu_robotu_comm
  "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kamu_robotu_comm
)

### Generating Module File
_generate_module_cpp(kamu_robotu_comm
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kamu_robotu_comm
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(kamu_robotu_comm_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(kamu_robotu_comm_generate_messages kamu_robotu_comm_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv" NAME_WE)
add_dependencies(kamu_robotu_comm_generate_messages_cpp _kamu_robotu_comm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kamu_robotu_comm_gencpp)
add_dependencies(kamu_robotu_comm_gencpp kamu_robotu_comm_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kamu_robotu_comm_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(kamu_robotu_comm
  "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/kamu_robotu_comm
)

### Generating Module File
_generate_module_eus(kamu_robotu_comm
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/kamu_robotu_comm
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(kamu_robotu_comm_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(kamu_robotu_comm_generate_messages kamu_robotu_comm_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv" NAME_WE)
add_dependencies(kamu_robotu_comm_generate_messages_eus _kamu_robotu_comm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kamu_robotu_comm_geneus)
add_dependencies(kamu_robotu_comm_geneus kamu_robotu_comm_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kamu_robotu_comm_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(kamu_robotu_comm
  "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kamu_robotu_comm
)

### Generating Module File
_generate_module_lisp(kamu_robotu_comm
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kamu_robotu_comm
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(kamu_robotu_comm_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(kamu_robotu_comm_generate_messages kamu_robotu_comm_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv" NAME_WE)
add_dependencies(kamu_robotu_comm_generate_messages_lisp _kamu_robotu_comm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kamu_robotu_comm_genlisp)
add_dependencies(kamu_robotu_comm_genlisp kamu_robotu_comm_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kamu_robotu_comm_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(kamu_robotu_comm
  "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/kamu_robotu_comm
)

### Generating Module File
_generate_module_nodejs(kamu_robotu_comm
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/kamu_robotu_comm
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(kamu_robotu_comm_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(kamu_robotu_comm_generate_messages kamu_robotu_comm_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv" NAME_WE)
add_dependencies(kamu_robotu_comm_generate_messages_nodejs _kamu_robotu_comm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kamu_robotu_comm_gennodejs)
add_dependencies(kamu_robotu_comm_gennodejs kamu_robotu_comm_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kamu_robotu_comm_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(kamu_robotu_comm
  "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kamu_robotu_comm
)

### Generating Module File
_generate_module_py(kamu_robotu_comm
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kamu_robotu_comm
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(kamu_robotu_comm_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(kamu_robotu_comm_generate_messages kamu_robotu_comm_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kippur/catkin_ws/src/oko_slam/ros_ws/src/kamu_robotu/kamu_robotu_comm/srv/kamu_cmd.srv" NAME_WE)
add_dependencies(kamu_robotu_comm_generate_messages_py _kamu_robotu_comm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kamu_robotu_comm_genpy)
add_dependencies(kamu_robotu_comm_genpy kamu_robotu_comm_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kamu_robotu_comm_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kamu_robotu_comm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kamu_robotu_comm
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(kamu_robotu_comm_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/kamu_robotu_comm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/kamu_robotu_comm
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(kamu_robotu_comm_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kamu_robotu_comm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kamu_robotu_comm
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(kamu_robotu_comm_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/kamu_robotu_comm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/kamu_robotu_comm
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(kamu_robotu_comm_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kamu_robotu_comm)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kamu_robotu_comm\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kamu_robotu_comm
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(kamu_robotu_comm_generate_messages_py std_msgs_generate_messages_py)
endif()
