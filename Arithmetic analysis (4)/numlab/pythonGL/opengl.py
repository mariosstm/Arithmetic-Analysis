import time

from OpenGL.GLU import *

from OpenGL.GL import *
from OpenGL.GL.shaders import *

import pyrr
from pyrr import Matrix44, Vector4, Vector3, Quaternion

import pygame
from pygame.locals import *
import numpy    


width = 640
height = 480

#Global Variables
vertices = numpy.array([0.0, 0.5, 0.0,
                           -0.5, -0.5, 0.0,
                            0.5, -0.5, 0.0], numpy.float32)
normals = numpy.array([0.0, 0.0, 1.0,
                           0.0, 0.0, -1.0,
                           0.0, 0.0, -1.0], numpy.float32)
mvpLoc = None
textureID = None
textLoc = None
#==============

def load_opengl_texture(filename):
    img = pygame.image.load(filename)
    imgdata = pygame.image.tostring(img, "RGBA", 1)
    imgwidth, imgheight = img.get_size()
    
    # img = Image.open(filename)
    # imgdata = numpy.array(list(img.getdata()), 'B')
    # imgwidth, imgheight = img.size[0], img.size[1]
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
    texid = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, texid)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgwidth, imgheight, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, imgdata)

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)

    return texid


def getFileContents(filename):
    return open(filename, 'r').read()


def init():
    #Creating Window
    pygame.init()
    pygame.display.set_mode((width, height), HWSURFACE|OPENGL|DOUBLEBUF)


    #Program compiling
    vertexShader = compileShader(getFileContents("pythonGL/triangle.vert"), GL_VERTEX_SHADER)
    fragmentShader = compileShader(getFileContents("pythonGL/triangle.frag"), GL_FRAGMENT_SHADER)
    program = glCreateProgram()
    glAttachShader(program, vertexShader)
    glAttachShader(program, fragmentShader)
    glBindAttribLocation(program, 0, "vPosition")
    glLinkProgram(program)

    #gluPerspective(45, 1, 0.1, 50.0)

    glViewport(0, 0, width, height)

    glClearColor(0.2, 0.2, 0.2, 1.0)
    
    glEnable(GL_DEPTH_TEST)
    glDepthFunc(GL_LEQUAL)

    glUseProgram(program)

    global textureID
    textureID = load_opengl_texture("pythonGL/texture.jpg")

    global textLoc
    textLoc = glGetUniformLocation(program, "text1")

    global mvpLoc
    mvpLoc = glGetUniformLocation(program, "u_MVP")

    

def draw(vertices, normals, uvs):
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices)
    glEnableVertexAttribArray(0)

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, normals)
    glEnableVertexAttribArray(1)

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, uvs)
    glEnableVertexAttribArray(2)

    model_matrix = pyrr.matrix44.create_from_translation(Vector3([-0.6, -0.4, 0])) # scale_matrix * rot_matrix * trans_matrix
    view_matrix = pyrr.matrix44.create_look_at(numpy.array([0, 0, 2.3]), numpy.array([0, 0, 0]), numpy.array([0, 1, 0])) #pyrr.matrix44.create_identity() # 
    proj_matrix = pyrr.matrix44.create_perspective_projection_matrix(45.0, 1280/720, 0.1, 100.0)
    mvp_matrix =  pyrr.matrix44.multiply(model_matrix , view_matrix )
    mvp_matrix =  pyrr.matrix44.multiply(mvp_matrix, proj_matrix)

    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp_matrix)

    glActiveTexture(GL_TEXTURE0)
    glBindTexture(GL_TEXTURE_2D, textureID)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT)
    glUniform1i(textLoc, 0)



    glDrawArrays(GL_TRIANGLES, 0, int(vertices.shape[0]/3))

    pygame.display.flip()

def create_list_of_vertices(points):
    vertices_list = []
    normals_list = []
    uvs_list = []

    dimensions = points.shape
    m_cross = numpy.cross
    m_asarray = numpy.asarray

    for i in range(0, dimensions[0] - 1):
        for j in range (0, dimensions[1] - 1):
            vertex1 = m_asarray(points[i,j,:])
            vertex2 = m_asarray(points[i,j+1,:])
            vertex3 = m_asarray(points[i+1,j+1,:])
            vertex4 = m_asarray(points[i+1,j,:])

            #triangle1
            vertices_list.append(vertex1)
            vertices_list.append(vertex2)
            vertices_list.append(vertex3)

            normal = m_cross(vertex1 - vertex2,vertex1 - vertex3)
            normal = normal/numpy.linalg.norm(normal)
            normals_list.append(normal)
            normals_list.append(normal)
            normals_list.append(normal)

            uvs_list.append(m_asarray([float(i)/dimensions[0], float(j)/dimensions[1]]))
            uvs_list.append(m_asarray([float(i)/dimensions[0], float(j+1)/dimensions[1]]))
            uvs_list.append(m_asarray([float(i+1)/dimensions[0], float(j+1)/dimensions[1]]))

            #triangle2
            vertices_list.append(vertex1)
            vertices_list.append(vertex3)
            vertices_list.append(vertex4)

            normal = m_cross(vertex1 - vertex3,vertex1 - vertex4)
            normal = normal/numpy.linalg.norm(normal)
            normals_list.append(normal)
            normals_list.append(normal)
            normals_list.append(normal)
            
            uvs_list.append(m_asarray([float(i)/dimensions[0], float(j)/dimensions[1]]))
            uvs_list.append(m_asarray([float(i+1)/dimensions[0], float(j+1)/dimensions[1]]))
            uvs_list.append(m_asarray([float(i+1)/dimensions[0], float(j)/dimensions[1]]))

            

    uvs_list = m_asarray(uvs_list).reshape(-1)
    normals_list = m_asarray(normals_list).reshape(-1)
    vertices_list = m_asarray(vertices_list).reshape(-1)
    #print(final_list.shape)
    return (vertices_list, normals_list, uvs_list)


def closeAll():
    pygame.quit()
    quit()


def main():

    global vertices 
    global normals

    init()

    X0 = numpy.zeros((10, 10, 3))
    test = create_list_of_vertices(X0)
    print(test[0].shape)


    print(vertices.shape)
    clock = pygame.time.Clock()
    while(True):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                break
        #clock.tick()
        #t = clock.get_time()
        #(temp1,temp2) = create_list_of_vertices(X0)
        #print(temp2.shape)
        #print(temp1.shape)
        #print("========")
        draw(vertices, normals)
        #clock.tick()
        #print("time passed (ms): " + str(clock.get_time() - t))


if (__name__ == '__main__'):
    main()
