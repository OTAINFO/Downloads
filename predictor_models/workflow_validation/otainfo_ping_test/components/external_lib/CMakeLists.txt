set(OBJ_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/model.cc.obj 
   ${CMAKE_CURRENT_SOURCE_DIR}/otainfo_predictor.cc.obj 
)

# Register as a component
idf_component_register(
    SRCS ${OBJ_FILES} )