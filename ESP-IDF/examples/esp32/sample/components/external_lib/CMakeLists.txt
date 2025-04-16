set(OBJ_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/OTAinfo.c.obj 
   ${CMAKE_CURRENT_SOURCE_DIR}/OTAinfo_comm.c.obj 
)



# Register as a component
idf_component_register(
    SRCS ${OBJ_FILES}
    PRIV_REQUIRES json
    INCLUDE_DIRS "."  "$ENV{IDF_PATH}/components/json/cJSON"
)
