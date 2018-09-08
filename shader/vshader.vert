#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color;  //kolor wierzcholka (na razie ignorowany)
in vec4 normal; //wektor normalny w wierzcholku w przestrzeni modelu


//Zmienne interpolowane
out vec4 iC; //Kolor wyliczony w vertex shaderze
out vec4 l;
out vec4 n;
out vec4 v;

void main(void) {
    vec4 lp=vec4(0,0,-6,1);

    l=normalize(V*lp-V*M*vertex);
    n=normalize(V*M*normal); 
	v=normalize(vec4(0,0,0,1) - V*M*vertex);

    iC=color;

	gl_Position=P*V*M*vertex;
}


