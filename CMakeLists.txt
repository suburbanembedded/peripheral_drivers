
add_library(periph_driv
	src/LTC6813/LTC6813.cpp
	src/LTC6813/PEC.cpp
)

target_include_directories(periph_driv PUBLIC
	include
)

target_link_libraries(periph_driv PUBLIC
	emb_util
)
