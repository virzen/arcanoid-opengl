#version 330

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 iC; //Zmienna interpolowana - kolor wyliczony w vertex shaderze
in vec4 l;
in vec4 n;
in vec4 v;

void main(void) {

	// wartosci dla modelu phonga
    vec4 ka=vec4(0,0,0,0);
    vec4 kd=iC;
	vec4 ks=vec4(1, 1, 1, 0);

    vec4 la=vec4(0,0,0,0);
    vec4 ld=vec4(1,1,1,1);
	vec4 ls=vec4(1,1,1,0);

	vec4 ml=normalize(l);
	vec4 mn=normalize(n);
	vec4 mv=normalize(v);



	vec4 r=reflect(-ml, mn);

    float nl=max(dot(mn,ml),0);
	float rv=pow(max(0,dot(r,mv)), 50);

    pixelColor=ka*la+kd*ld*vec4(nl,nl,nl,1)+ks*ls*rv; 
}
