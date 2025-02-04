// Based on templates from learnopengl.com
#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>

#include "OrthoCamera.hpp"
#include "PerspCamera.hpp"
#include "HitRecord.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Plane.hpp"
#include "Material.hpp"
#include "DirectionalLight.hpp"

const int objectCount = 7;
const int maxRecursionDepth = 1;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void renderImage(Camera* camera, unsigned char* image, int imageWidth, int imageHeight, Surface* (&objects)[objectCount], 
                 DirectionalLight light);
glm::vec3 shade(Ray &ray, DirectionalLight &light, HitRecord& hitRecord, glm::vec3 color, Surface* (&objects)[objectCount], int &recursionDepth);
HitRecord firstHit(Surface* (&objects)[objectCount], Ray ray);
void writePPM(const char* filename, unsigned char* data, int width, int height);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

bool SWAP = false;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"    
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
	"gl_Position = vec4(aPos, 1.0);\n"
	"ourColor = aColor;\n"
	"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"
    "uniform sampler2D texture1;\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture(texture1, TexCoord);\n"
    "}\n\0";
    

int main()
{
    int input;
    std::cout << "Press 0 for Orthographic View or 1 for Perspective View." << std::endl;
    std::cin >> input;
    std::cout << std::endl << input << " is the selected option." << std::endl;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Display RGB Array", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // GLEW: load all OpenGL function pointers
    glewInit();

    // build and compile the shaders
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        1.0f,  -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Image Resolution
    const int imageWidth  = 1024; // keep it in powers of 2!
    const int imageHeight = 1024; // keep it in powers of 2!
    // Create the image (RGB Array) to be displayed
    unsigned char* image = new unsigned char[imageWidth*imageHeight*3];

    Camera *camera;

    // Perspective
    if(input) { 
        glm::vec3 viewPoint = glm::vec3(1,2,-1);
        glm::vec3 cameraTarget = glm::vec3(1.4,1.4,3);
        glm::vec3 viewDir = glm::normalize(cameraTarget - viewPoint);
        glm::vec3 upward = glm::vec3(0,1,0);
        float focalLength = 10;

        PerspCamera perspCamera(viewPoint, viewDir, upward, imageWidth, imageHeight, focalLength);

        camera = &perspCamera;
    }
    // Orthographic
    else {
        glm::vec3 viewPoint = glm::vec3(5,10,-5);
        glm::vec3 cameraTarget = glm::vec3(3,6,5);
        glm::vec3 viewDir = glm::normalize(cameraTarget - viewPoint);
        glm::vec3 upward = glm::vec3(0,1,0);

        OrthoCamera orthoCamera(viewPoint, viewDir, upward, imageWidth, imageHeight);

        camera = &orthoCamera;
    }
    

    float I = 1; // Between 0-1
    glm::vec3 lightDirection(20,30,0);
    DirectionalLight dLight(I, lightDirection);

    // Plane
    glm::vec3 planeOrigin(0,0,0);
    glm::vec3 planeColor(255,255,255);
    Material planeMaterial(planeColor, 0.3f, 0.3f, 0.4f, 0.5f, true);
    glm::vec3 planeNormal(0,1,0);
    Plane plane(planeOrigin, planeMaterial, planeNormal);

    // Sphere 1
    glm::vec3 sphereOrigin1(2,2,10);
    float radius1 = 2;
    glm::vec3 color1(255,0,0);
    Material sphereMaterial(color1, 0.2f , 0.4f, 0.4f, 0.5f, false);
    Sphere sphere1(sphereOrigin1, sphereMaterial, radius1); 

    // Sphere 2
    glm::vec3 sphereOrigin2(-2,1,10);
    float radius2 = 1;
    glm::vec3 color2(0,255,0);
    Material sphere2Mat(color2, 0.2f , 0.2f, 0.6f, 0.5f, false);
    Sphere sphere2(sphereOrigin2, sphere2Mat, radius2);

    // Tetrahedron (4 triangles)
    glm::vec3 origin(0,0,0);
    glm::vec3 tColor1(0,255,255);
    glm::vec3 tColor2(255,255,0);
    Material triangleMat1(tColor1, 0.4f, 0.3f, 0.3f, 0.5f, false);

    glm::vec3 vertex1 = glm::vec3(4,0,3);
    glm::vec3 vertex2 = glm::vec3(2,0,5);
    glm::vec3 vertex3 = glm::vec3(2,0,3);
    glm::vec3 vertex4 = glm::vec3(3,1,4);

    Triangle backTriangle2(origin, triangleMat1, vertex4, vertex1, vertex2);
    Triangle bottomTriangle2(origin, triangleMat1 , vertex1, vertex2, vertex3);
    Triangle leftTriangle2(origin, triangleMat1, vertex1, vertex3, vertex4);
    Triangle rightTriangle2(origin, triangleMat1, vertex2, vertex3, vertex4);


    // Surface* objects[objectCount] = {&sphere1};
    Surface* objects[objectCount] = {&sphere1, &sphere2, &backTriangle2, &bottomTriangle2, &leftTriangle2, 
                                    &rightTriangle2, &plane};
    


    // FOR MOVIE CREATION
    // std::string directory = "images/";

    // int f_s = 20; // frames/sec
    // int T = 12; // seconds for one full rotation

    // int numImages = T * f_s;

    // for (int t = 0; t < numImages; ++t) {

    //     glm::vec3 viewPoint = glm::vec3(20,2,-10);
        
    //     viewPoint.x = viewPoint.x * glm::sin((2 * M_PI * t)/ (T * f_s));
    //     viewPoint.z = viewPoint.z * glm::cos((2 * M_PI * t)/ (T * f_s));

    //     glm::vec3 cameraTarget = glm::vec3(1.4,1.4,3);
    //     glm::vec3 viewDir = glm::normalize(cameraTarget - viewPoint);
    //     glm::vec3 upward = glm::vec3(0,1,0);
    //     float focalLength = 10;

    //     PerspCamera perspCamera(viewPoint, viewDir, upward, imageWidth, imageHeight, focalLength);

    //     camera = &perspCamera;

    //     // Generate filename with leading zeros
    //     std::string filename = directory + "output_" + std::to_string(t);
    //     filename.insert(filename.begin() + directory.length() + 7, 3 - std::to_string(t).length(), '0'); // insert leading zeros
    //     filename += ".ppm";

    //     renderImage(camera, image, imageWidth, imageHeight, objects, dLight);
        
    //     // Write image data to the file
    //     writePPM(filename.c_str(), image, imageWidth, imageHeight);
        
    //     std::cout << "Generated: " << filename << std::endl;
    // }

    // Ray Equation: p(t) = e + t(s − e).
    renderImage(camera, image, imageWidth, imageHeight, objects, dLight);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();    
    return 0;
}

void renderImage(Camera* camera, unsigned char* image, int imageWidth, int imageHeight, Surface* (&objects)[objectCount], 
                DirectionalLight light) {

    for(int i = 0; i < imageWidth; i++)
    {
        for (int j = 0; j < imageHeight; j++)
        {
            int recursionDepth = 0;
            // compute (u,v) to get coordinates of pixel's position on the image plane, with respect to e
            float u = camera->DeterminePixelU(j, imageWidth); // FLIPPED I AND J AND NOW WORKS????
            float v = camera->DeterminePixelV(i, imageHeight);

            // create ray from pixel position
            glm::vec3 o = camera->GenerateRayOrigin(u,v); 
            glm::vec3 d = camera->GenerateRayDirection(u,v);

            Ray ray(o,d);
            
            HitRecord hitRecord;
            glm::vec3 baseColor(0,0,0);
            glm::vec3 color = shade(ray, light, hitRecord, baseColor, objects, recursionDepth);
                
            
            if (hitRecord.t == INFINITY) { // if t is infinity (no hit)
                color = glm::vec3(0,0,0);
            }
            
            int idx = (i * imageWidth + j) * 3;
            image[idx] = color.x;
            image[idx+1] = color.y;
            image[idx+2] = color.z;

        }
    }

    unsigned char *data = &image[0];
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

glm::vec3 shade(Ray &ray, DirectionalLight &light, HitRecord& hitRecord, glm::vec3 color, Surface* (&objects)[objectCount], int &recursionDepth) {
            
            hitRecord = firstHit(objects, ray);
            if (hitRecord.t != INFINITY) {
                color = light.illuminate(ray, hitRecord);
            }
            
            // Mirror Reflection (Glaze)
            // source: https://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/reflection_refraction.pdf
            if (hitRecord.t != INFINITY) {
                if (recursionDepth < maxRecursionDepth) {
                    if (hitRecord.s->material.glazed) {
                        // glm::vec3 reflectionDir = glm::normalize(-2 * (glm::dot(ray.getDirection(), hitRecord.n)) * hitRecord.n + ray.getDirection());
                        glm::vec3 reflectionDir = ray.getDirection() - 2 * (glm::dot(ray.getDirection(), hitRecord.n)) * hitRecord.n;
                        float epsilon = 0.01f;
                        glm::vec3 reflectOrigin = ray.evaluate(hitRecord.t) + epsilon*(reflectionDir);
                        Ray reflectRay = Ray(reflectOrigin, reflectionDir);

                        recursionDepth += 1;
                        HitRecord hitRecordR = HitRecord();
                        glm::vec3 L_m = hitRecord.s->material.k_m * shade(reflectRay, light, hitRecordR, color, objects, recursionDepth);
                        color += L_m;
                        color = glm::clamp(color, 0.0f, 255.0f); // to prevent overflow
                    }
                }
            }
            return color;
}

HitRecord firstHit(Surface* (&objects)[objectCount], Ray ray) {
    HitRecord firstHit;
    float tMin = INFINITY;
    for (int i = 0; i < objectCount; i++) {
        HitRecord hit = objects[i]->hit(ray, 0, INFINITY);
        if (hit.t < tMin) {
            tMin = hit.t;
            firstHit = hit;
        }
    }
    return firstHit;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// Creates image files for video
void writePPM(const char* filename, unsigned char* data, int width, int height) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error: Unable to open file for writing!" << std::endl;
        return;
    }

    file << "P6\n";
    file << width << " " << height << "\n";
    file << "255\n";

    // Write pixel data
    // Reversing the order of rows
    for (int y = height - 1; y >= 0; --y) {
        file.write(reinterpret_cast<char*>(data + y * width * 3), width * 3);
    }
    file.close();
}