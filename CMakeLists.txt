CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(opengl-arcanoid)

# OpenGL
FIND_PACKAGE(OpenGL REQUIRED)

IF (OPENGL_FOUND)
	MESSAGE(STATUS "OpenGL found.")
	MESSAGE(STATUS "OPENGL_INCLUDE_DIR:  '${OPENGL_INCLUDE_DIR}'")
	MESSAGE(STATUS "OPENGL_gl_LIBRARY:   '${OPENGL_gl_LIBRARY}'")
ELSE ()
	MESSAGE(WARNING "OpenGL NOT found!")
ENDIF ()
MESSAGE("")

IF (OPENGL_GLU_FOUND)
	MESSAGE(STATUS "GLU found.")
	MESSAGE(STATUS "OPENGL_INCLUDE_DIR:  '${OPENGL_INCLUDE_DIR}'")
	MESSAGE(STATUS "OPENGL_glu_LIBRARY:  '${OPENGL_glu_LIBRARY}'")
ELSE ()
	MESSAGE(WARNING "GLU NOT found!")
ENDIF ()
MESSAGE("")

# GLFW3
FIND_PACKAGE(glfw3 REQUIRED)

IF (OPENGL_GLU_FOUND) #TODO
	MESSAGE(STATUS "OpenGL found.")
	MESSAGE(STATUS "GLFW3_DIR:  '${GLFW3_DIR}'")
	MESSAGE(STATUS "GLFW3_LIB:  '${GLFW3_LIB}'")
ELSE ()
	MESSAGE(WARNING "GLU NOT found!")
ENDIF ()
MESSAGE("")

FIND_PACKAGE(GLUT REQUIRED)

MESSAGE(STATUS "OPENGL_INCLUDE_DIR:  '${OPENGL_INCLUDE_DIR}'")
MESSAGE(STATUS "GLUT_INCLUDE_DIRS:   '${GLUT_INCLUDE_DIR}'")
MESSAGE(STATUS "glfw3_INCLUDE_DIR:   '${glfw3_INCLUDE_DIR}'")

MESSAGE(STATUS "glfw3_INCLUDE_PATH:  '${glfw3_INCLUDE_PATH}'")
MESSAGE(STATUS "GLEW_INCLUDE_PATH:   '${GLEW_INCLUDE_PATH}'")
MESSAGE(STATUS "GLM_INCLUDE_PATH:    '${GLM_INCLUDE_PATH}'")

MESSAGE(STATUS "OPENGL_gl_LIBRARY:   '${OPENGL_gl_LIBRARY}'")
MESSAGE(STATUS "OPENGL_glu_LIBRARY:  '${OPENGL_glu_LIBRARY}'")
MESSAGE(STATUS "glfw3_LIBRARY:       '${glfw3_LIBRARY}'")
MESSAGE(STATUS "GLEW_LIBRARY:        '${GLEW_LIBRARY}'")

LINK_DIRECTORIES(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(
		${GLFW3_DIR}
		${GLEW_INCLUDE_PATH}
		${GLM_INCLUDE_PATH}
)

SET(HEADER_FILES
		constants.h
		errors.h
		game.h
		models/model.h
		models/paddle/paddle.h
		models/horizontal-wall/horizontal-wall.h
		models/vertical-wall/vertical-wall.h
		models/brick/brick.h
		models/ball/ball.h
		shader/shader.h
		shader/shaders.h
		shader/color/color-shader.h
		shader/texture/texture-shader.h
		shader/metal/metal-shader.h)

SET(SOURCE_FILES
		main_file.cpp
		errors.cpp
		game.cpp
		models/model.cpp
		models/paddle/paddle.cpp
		models/horizontal-wall/horizontal-wall.cpp
		models/vertical-wall/vertical-wall.cpp
		models/brick/brick.cpp
		models/ball/ball.cpp
		shader/shader.cpp utils/obj_loader.cpp utils/obj_loader.h utils/does_collide.h utils/does_collide.cpp utils/bounce.cpp utils/bounce.h models/boundingBox/boundingBox.h models/boundingBox/boundingBox.cpp
		shader/shaders.cpp
		shader/color/color-shader.cpp
		shader/texture/texture-shader.cpp
		shader/metal/metal-shader.cpp)

ADD_EXECUTABLE(opengl-arcanoid
		${HEADER_FILES}
		${SOURCE_FILES}
		)

TARGET_LINK_LIBRARIES(opengl-arcanoid
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
		#/usr/local/lib/libglfw.so
		glfw
		${glfw3_LIBRARY}
		${GLEW_LIBRARY}
		)
