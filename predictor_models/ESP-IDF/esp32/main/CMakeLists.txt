# set(OBJ_FILES
#    ${CMAKE_CURRENT_SOURCE_DIR}/model.c.obj 
#    ${CMAKE_CURRENT_SOURCE_DIR}/otainfo_predictor.c.obj 
# )

# Register as a component
idf_component_register(
    SRCS main.cc 
    INCLUDE_DIRS "../components/external_lib")