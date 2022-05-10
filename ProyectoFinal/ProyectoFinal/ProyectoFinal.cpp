
// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 1024, HEIGHT = 720;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animacionGolem();


// Camera
Camera camera(glm::vec3(-4.5f, 2.0f, -1.8f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


// Light attributes
glm::vec3 lightPos(-4.5f, 4.0f, -1.8f);
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
float movx = 0.0f;
float movz = 0.0f;
bool ruta1 = true;
bool ruta2 = false;
bool ruta3 = false;
bool ruta4 = false;
bool ruta5 = false;
bool ruta6 = false;
bool ruta7 = false;
bool ruta8 = false;

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Iluminacion", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");
    Shader lampshader("Shaders/lamp.vs", "Shaders/lamp.frag");
    Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
    Shader Anim("Shaders/anim.vs", "Shaders/anim.frag");


    // Load models
    Model golem((char*)"Golem/Golem.obj");
    Model cuadro((char*)"Cuadro/cuadro.obj");
    Model librero((char*)"Librero/librero.obj");
    Model cofreArriba((char*)"Cofre/cofreArriba.obj");
    Model cofreAbajo((char*)"Cofre/cofreAbajo.obj");
    Model mesaEnchArriba((char*)"MesaEncantamientos/mesaEncantamientosArriba.obj");
    Model mesaEnchAbajo((char*)"MesaEncantamientos/mesaEncantamientosAbajo.obj");
    Model mesaCrafteo((char*)"MesaCrafteo/mesaCrafteo.obj");
    Model casa((char*)"Casa/Casa.obj");
    Model escaleras((char*)"Casa/escaleras.obj");
    Model casaCristales((char*)"Casa/CasaCristales.obj");
    Model pasto((char*)"Pasto/pasto.obj");
    Model velas((char*)"Velas/velas.obj");
    Model fuego((char*)"Velas/fuego.obj");


    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    float vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.Use();
        GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


        // Set lights properties
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.3f, 0.3f, 0.3f);//Cambiar brillo de la escena
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.3f, 0.3f, 0.3f);//Cambia el color general de la escena
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);




        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        //golem de nieve
        // Set material properties
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);//color
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.5f, 0.5f, 0.5f);//brillo 
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 256.0f);
        glm::mat4 model(1);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "trans"), 1.0f);

        model = glm::translate(model, glm::vec3(4.5f, -1.2f, -7.2f)+glm::vec3(movx,0,movz));
        model = glm::rotate(model, glm::radians(-90.0f+rot), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model,glm::vec3(4.0f,4.0f,4.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        golem.Draw(lightingShader);
        animacionGolem();

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.06f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuadro.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.9f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        librero.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.9f, 0.0f, -1.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        librero.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.9f, -0.2f, -1.8f));
        //model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.2, 1.2, 1.2));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        velas.Draw(lightingShader);

        model = glm::mat4(1);
        float time = glfwGetTime();
        model = glm::translate(model, glm::vec3(-0.9f, 1.65f, -1.8f));
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.6*glm::abs(glm::sin(time))+0.6, 0.6 * glm::abs(glm::sin(time)) + 0.6, 0.6 * glm::abs(glm::sin(time)) + 0.6));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        fuego.Draw(lightingShader);

        model = glm::mat4(1);
        float time2 = glfwGetTime();
        model = glm::translate(model, glm::vec3(-0.63f, 1.53f, -2.011f));
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.6 * glm::abs(glm::sin(time)) + 0.6, 0.6 * glm::abs(glm::sin(time)) + 0.6, 0.6 * glm::abs(glm::sin(time)) + 0.6));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        fuego.Draw(lightingShader);

        model = glm::mat4(1);
        float time3 = glfwGetTime();
        model = glm::translate(model, glm::vec3(-0.85f, 1.26f, -2.111f));
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.6 * glm::abs(glm::sin(time)) + 0.6, 0.6 * glm::abs(glm::sin(time)) + 0.6, 0.6 * glm::abs(glm::sin(time)) + 0.6));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        fuego.Draw(lightingShader);


        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-8.05f, 0.108f, -7.8f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f)* (float)glm::abs(glm::sin(glfwGetTime()*0.5)), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.8, 0.8, 0.8));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cofreArriba.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-8.05f, 0.108f, -7.8f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.8, 0.8, 0.8));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cofreAbajo.Draw(lightingShader);

        Anim.Use();
        
        GLint modelLoc = glGetUniformLocation(Anim.Program, "model");
        GLint viewLoc = glGetUniformLocation(Anim.Program, "view");
        GLint projLoc = glGetUniformLocation(Anim.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-6.3f, 0.2f, -7.2f));
        model = glm::rotate(model, glm::radians(-90.0f)+(float)glfwGetTime()*0.4f, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(Anim.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform1f(glGetUniformLocation(Anim.Program, "time"), glfwGetTime());
        mesaEnchArriba.Draw(Anim);

        lightingShader.Use();

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-6.3f, 0.0f, -7.2f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        mesaEnchAbajo.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.5f, 0.0f, -7.2f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        mesaCrafteo.Draw(lightingShader);        


        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.9f, -1.8f, 1.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        casa.Draw(lightingShader);


        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.631f, 0.745f, 0.294f);//color
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.1f, 0.1f, 0.1f);//brillo 
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 256.0f);
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.9f, -1.8f, 1.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pasto.Draw(lightingShader);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);//color
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.5f, 0.5f, 0.5f);//brillo 
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 256.0f);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.9f, -1.8f, 1.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        escaleras.Draw(lightingShader);


        glUniform1f(glGetUniformLocation(lightingShader.Program, "trans"), 0.7f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.9f, -1.8f, 1.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        casaCristales.Draw(lightingShader);
        glDisable(GL_BLEND);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "trans"), 1.0f);

        

        glBindVertexArray(0);




        lampshader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(lightPos.x, lightPos.y, lightPos.z));
        model = glm::scale(model, glm::vec3(0.02f));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

}

void animacionGolem(){
    if (ruta1) {
        rot = 0;
        movx -= 0.02;
        if (movx < -1.8f) {
            ruta1 = false;
            ruta2 = true;
        }
    }
    if (ruta2) {
        rot = 90.0f;
        movz += 0.02;
        if (movz > 1.8f) {
            ruta2 = false;
            ruta3 = true;
        }
    }
    if (ruta3) {
        rot = 180.0f;
        movx += 0.02;
        if (movx > 0.0f) {
            ruta3 = false;
            ruta4 = true;
        }
    }
    if (ruta4) {
        rot = 90.0f;
        movz += 0.02;
        if (movz > 3.6f) {
            ruta4 = false;
            ruta5 = true;
        }
    }
    if (ruta5) {
        rot = 0.0f;
        movx -= 0.02;
        if (movx < -1.8f) {
            ruta5 = false;
            ruta6 = true;
        }
    }
    if (ruta6) {
        rot = -90.0f;
        movz -= 0.02;
        if (movz < 1.8f) {
            ruta6 = false;
            ruta7 = true;
        }
    }
    if (ruta7) {
        rot = 180.0f;
        movx += 0.02;
        if (movx > 0.0f) {
            ruta7 = false;
            ruta8 = true;
        }
    }
    if (ruta8) {
        rot = -90.0f;
        movz -= 0.02;
        if (movz < 0.0f) {
            ruta8 = false;
            ruta1 = true;
        }
    }

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}


