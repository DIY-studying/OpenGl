#shader vertex
 #version 330 core
 layout(location=0) in vec4 aPosition;
 layout(location=1) in vec2 aTexCoord;

 out vec2 TexCoord;
 uniform mat4 u_MVP;

 void main()
 {
 gl_Position=u_MVP*aPosition;
 TexCoord=aTexCoord;
 };

#shader fragmentShader
 #version 330 core
 out vec4 fragment_Color;

 in vec2 TexCoord;
 uniform sampler2D ourTexture;
 uniform vec4 u_Color;
 void main()
 {
		fragment_Color=texture(ourTexture,TexCoord);
		//fragment_Color=u_Color;
 };