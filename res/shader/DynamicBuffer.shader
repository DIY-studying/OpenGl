#shader vertex
 #version 330 core
 layout(location=0) in vec4 aPosition;
 layout(location=1) in vec2 aTexCoord;
 layout(location=2) in float aTextureIndex;


 out vec2 TexCoord;
 out float textureIndex;


 void main()
 {
 textureIndex=aTextureIndex;
 gl_Position=aPosition;
 TexCoord=aTexCoord;
 };

#shader fragmentShader
 #version 330 core
 out vec4 fragment_Color;

 in vec2 TexCoord;
 in float textureIndex;
 uniform sampler2D ourTexture[2];
 uniform vec4 u_Color;
 void main()
 {
		fragment_Color=texture(ourTexture[int(textureIndex)],TexCoord);
		//fragment_Color=vec4(1,0,0,1);
 };