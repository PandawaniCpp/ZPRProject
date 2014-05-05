uniform sampler2D texture;
uniform sampler2D sandTexture;
uniform sampler2D groundTexture;
uniform sampler2D permutationVector;
uniform float time;
uniform float resolutionX;
uniform float resolutionY;
uniform float offsetX;
uniform float offsetY;
uniform float width;
uniform float height;
uniform float zoom;
uniform float persistence;
uniform float octaves;
uniform float deepWater;
uniform float shallowWater;
uniform float sand;

float fade(float t){
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float lerp(float t, float a, float b){
	return a + t * (b - a);
}

float grad(int hash, float x, float y, float z){
	int h = hash & 15;
	// Convert lower 4 bits of hash inot 12 gradient directions
	float u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float noise2d(float x, float y){
	int X = int(x) & 255;
	int Y = int(y) & 255;

	// Find relative x, y,z of point in cube
	x -= int(x);
	y -= int(y);

	// Compute fade curves for each of x, y, z
	float u = fade(x);
	float v = fade(y);

	// Hash coordinates of the 8 cube corners
	int A  =  int(256 * texture2D(permutationVector, vec2( (X % 16) * 0.0675, X * 0.00390625) ).x) + Y;
	int AA =  int(256 * texture2D(permutationVector, vec2( (A % 16) * 0.0675, A * 0.00390625) ).x);
	int AB =  int(256 * texture2D(permutationVector, vec2( ((A+1) % 16) * 0.0675, (A+1) * 0.00390625) ).x);
	int B  =  int(256 * texture2D(permutationVector, vec2( ((X+1) % 16) * 0.0675, (X+1) * 0.00390625) ).x) + Y;
	int BA =  int(256 * texture2D(permutationVector, vec2( (B % 16) * 0.0675, B * 0.00390625) ).x);
	int BB =  int(256 * texture2D(permutationVector, vec2( ((B+1) % 16) * 0.0675, (B+1) * 0.00390625) ).x);

	// Add blended results from 8 corners of cube
	float res = mix(mix(grad(int(256 * texture2D(permutationVector, vec2( (AA % 16) * 0.0675, AA * 0.00390625)).x), x, y, 0), 
						grad(int(256 * texture2D(permutationVector, vec2( (BA % 16) * 0.0675, BA * 0.00390625)).x), x - 1, y, 0), 
						u), 
						mix(grad(int(256 * texture2D(permutationVector, vec2( (AB % 16) * 0.0675, AB * 0.00390625)).x), x, y - 1, 0), 
							grad(int(256 * texture2D(permutationVector, vec2( (BB % 16) * 0.0675, BB * 0.00390625)).x), x - 1, y - 1, 0), 
							u), v);
	return res;
}

//Jedna warstwa szumu perlina, zwraca z zakresu -1--0--1
float noise(float x, float y, float z){
	int X = int(x) & 255;
	int Y = int(y) & 255;
	int Z = int(z) & 255;

	// Find relative x, y,z of point in cube
	x -= int(x);
	y -= int(y);
	z -= int(z);

	// Compute fade curves for each of x, y, z
	float u = fade(x);
	float v = fade(y);
	float w = fade(z);

	// Hash coordinates of the 8 cube corners
	int A  =  int(256 * texture2D(permutationVector, vec2( (X % 16) * 0.0675, X * 0.00390625) ).x) + Y;
	int AA =  int(256 * texture2D(permutationVector, vec2( (A % 16) * 0.0675, A * 0.00390625) ).x) + Z;
	int AB =  int(256 * texture2D(permutationVector, vec2( ((A+1) % 16) * 0.0675, (A+1) * 0.00390625) ).x) + Z;
	int B  =  int(256 * texture2D(permutationVector, vec2( ((X+1) % 16) * 0.0675, (X+1) * 0.00390625) ).x) + Y;
	int BA =  int(256 * texture2D(permutationVector, vec2( (B % 16) * 0.0675, B * 0.00390625) ).x) + Z;
	int BB =  int(256 * texture2D(permutationVector, vec2( ((B+1) % 16) * 0.0675, (B+1) * 0.00390625) ).x) + Z;

	// Add blended results from 8 corners of cube
	float res = lerp(w, 
					lerp(v, 
						lerp(u, 
							grad(int(256 * texture2D(permutationVector, vec2( (AA % 16) * 0.0675, AA * 0.00390625)).x), x, y, z), 
							grad(int(256 * texture2D(permutationVector, vec2( (BA % 16) * 0.0675, BA * 0.00390625)).x), x - 1, y, z)), 
							lerp(u, 
								grad(int(256 * texture2D(permutationVector, vec2( (AB % 16) * 0.0675, AB * 0.00390625)).x), x, y - 1, z), 
								grad(int(256 * texture2D(permutationVector, vec2( (BB % 16) * 0.0675, BB * 0.00390625)).x), x - 1, y - 1, z))), 
									lerp(v, 
									lerp(u, 
										grad(int(256 * texture2D(permutationVector, vec2( ( (AA + 1) % 16) * 0.0675, (AA + 1) * 0.00390625)).x), x, y, z - 1), 
										grad(int(256 * texture2D(permutationVector, vec2( ( (BA + 1) % 16) * 0.0675, (BA + 1) * 0.00390625)).x), x - 1, y, z - 1)), 
										lerp(u, 
											grad(int(256 * texture2D(permutationVector, vec2( ( (AB + 1) % 16) * 0.0675, (AB + 1) * 0.00390625)).x), x, y - 1, z - 1), 
											grad(int(256 * texture2D(permutationVector, vec2( ( (BB + 1) % 16) * 0.0675, (BB + 1) * 0.00390625)).x), x - 1, y - 1, z - 1))));
	return res;
}

//suma fraktalna szumów
float sum1(float x, float y, float z){
	float t = 1.0;
	float amplitude = 1.0;
	float frequency = 1;
	
	if (x > 0.6*width) {
		t -= 2.0*(25.0 / 4.0) * pow((x - width*0.6), 2) / pow(width, 2);
	}
	else if (x < 0.4f*width) {
		t -= 2.0*(25.0 / 4.0) * pow((width*0.4 - x), 2) / pow(width, 2);
	}
	if (y > 0.6*height) {
		t -= 2.0*(25.0 / 4.0) * pow((y - height*0.6), 2) / pow(height, 2);
	}
	else if (y < 0.4*height) {
		t -= 2.0*(25.0 / 4.0) * pow((height*0.4 - y), 2) / pow(height, 2);
	}

	for (int i = 0; i < octaves; i++) {
		t += noise2d( ((x*frequency) / zoom), ((y*frequency) / zoom))*amplitude;
		amplitude *= persistence;
		frequency *= 2.5;
	}
	
	if (t < -1.0) {
		t = -1.0;
	}

	if(x > width || x < 0.0 || y > height || y < 0){
		t = 1.0;
	}

	if (t > 1.0) {
		t = 1.0;
	}

	return (t+1)/2.0;
}

float sum2(float x, float y, float z){
	float t = 0.0;
	float amplitude = 1.0;
	float frequency = 1;

	for (int i = 0; i < 2; i++) {
		t += abs(noise( ((x*frequency) / 200), ((y*frequency) / 200), z)*amplitude);
		amplitude *= 0.2;
		frequency *= 2;
	}

	return t;
}


//odwracamy wartoœci szumu np 0.3 -> 0.7 0.2-> 0.8 itd.
float inverse(float t){
	return abs(t-1);
}

void main() {
	float offset0 = 0.0025;
	float wave = 0.0006*sin(0.6 * time + (2*(gl_FragCoord.x + offsetX) + 7*(gl_FragCoord.y - offsetY))/(resolutionX*resolutionY/1000.0))
							+ 0.0006*cos(-0.697 * time + (1.3*(gl_FragCoord.x + offsetX) + 4.8*(gl_FragCoord.y - offsetY))/(resolutionX*resolutionY/1000.0));
	
	float offset00 =  0.001 + 0.0005*sin(-2*time + (7*(gl_FragCoord.x + offsetX) + 2*(gl_FragCoord.y - offsetY))/(resolutionX*resolutionY/1000.0));
	float offset1 = 0.008;
	float offset2 = 0.004;
	float offset22 = offset2 - wave;
	float offset3 = 0.015;
	float offset4 = 0.020;
	float k = sum1(gl_FragCoord.x + offsetX , (resolutionY - gl_FragCoord.y) + offsetY, 0);
	float c = inverse(sum2(gl_FragCoord.x + offsetX , (resolutionY - gl_FragCoord.y) + offsetY, time)/3);
	float a = (noise((gl_FragCoord.x + offsetX) * 0.01, ((resolutionY - gl_FragCoord.y) + offsetY) * 0.01, 0))*0.5 + 1;
	vec3 pixel;
	vec3 deepCol = vec3(0, 0.05, 0.25) * c;
	
	vec3 shallowCol = vec3(0, 0.07, 0.3) * c;
	vec3 sandCol = texture2D(sandTexture, vec2((gl_FragCoord.x + offsetX)/(resolutionX/3.0), ((resolutionY - gl_FragCoord.y) + offsetY)/(resolutionX/3.0))).xyz; // = vec3(1.0, 0.8, 0.4) * k;
	vec3 grassCol = texture2D(texture, vec2((gl_FragCoord.x + offsetX)/(resolutionX/3.0), ((resolutionY - gl_FragCoord.y) + offsetY)/(resolutionX/3.0))).xyz; // = vec3(0.2, 0.6, 0.1) * k;
	vec3 kk = vec3(k);
	float t;
	float shallowWaterWaves = shallowWater + wave;
							
	if ( k < deepWater - offset3){
		pixel = deepCol;
	}
	else if(k < deepWater){
		t = fade((k + offset3 - deepWater)/offset3);
		pixel = mix(deepCol, shallowCol, t); 
	}
	else if (k < shallowWater - offset22){
		pixel = shallowCol;
	}
	else if (k < shallowWaterWaves){
		t = fade((k - shallowWater + offset22)/(shallowWaterWaves - shallowWater + offset22));
		pixel = mix(shallowCol, (sandCol + 1.4*shallowCol)/2, t);
	}
	else if (k < shallowWaterWaves + offset00){
		t = fade((k - shallowWaterWaves)/(offset00));
		pixel = mix((1.4*shallowCol + sandCol) * 0.5, (2*sandCol+2*shallowCol) * 0.5, t);
	}
	else if(k < sand - offset1){
		pixel = sandCol;
	}
	else if(k < sand){
		t = fade((k + offset1- sand)/offset1);
		t = pow(t, a*2);
		//t -=t*a;
		//t +=t*a;
		pixel = mix(sandCol, grassCol, t); 	

	}
	else{
		pixel = grassCol;
	}
	
	gl_FragColor = vec4(pixel, 1.0);
}