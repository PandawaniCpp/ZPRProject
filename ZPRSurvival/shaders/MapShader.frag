uniform sampler2D texture;
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

vec3 lerpV(float t, vec3 a, vec3 b){
	return a + t * (b - a);
}

float grad(int hash, float x, float y, float z){
	int h = hash & 15;
	// Convert lower 4 bits of hash inot 12 gradient directions
	float u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
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
	int A  =  int(256 * texture2D(permutationVector, vec2( (X % 16) / 16.0, X / 256.0) ).x) + Y;
	int AA =  int(256 * texture2D(permutationVector, vec2( (A % 16) / 16.0, A / 256.0) ).x) + Z;
	int AB =  int(256 * texture2D(permutationVector, vec2( ((A+1) % 16) / 16.0, (A+1) / 256.0) ).x) + Z;
	int B  =  int(256 * texture2D(permutationVector, vec2( ((X+1) % 16) / 16.0, (X+1) / 256.0) ).x) + Y;
	int BA =  int(256 * texture2D(permutationVector, vec2( (B % 16) / 16.0, B / 256.0) ).x) + Z;
	int BB =  int(256 * texture2D(permutationVector, vec2( ((B+1) % 16) / 16.0, (B+1) / 256.0) ).x) + Z;

	// Add blended results from 8 corners of cube
	float res = lerp(w, 
					lerp(v, 
						lerp(u, 
							grad(int(256 * texture2D(permutationVector, vec2( (AA % 16) / 16.0, AA / 256.0)).x), x, y, z), 
							grad(int(256 * texture2D(permutationVector, vec2( (BA % 16) / 16.0, BA / 256.0)).x), x - 1, y, z)), 
							lerp(u, 
								grad(int(256 * texture2D(permutationVector, vec2( (AB % 16) / 16.0, AB / 256.0)).x), x, y - 1, z), 
								grad(int(256 * texture2D(permutationVector, vec2( (BB % 16) / 16.0, BB / 256.0)).x), x - 1, y - 1, z))), 
									lerp(v, 
									lerp(u, 
										grad(int(256 * texture2D(permutationVector, vec2( ( (AA + 1) % 16) / 16.0, (AA + 1) / 256.0)).x), x, y, z - 1), 
										grad(int(256 * texture2D(permutationVector, vec2( ( (BA + 1) % 16) / 16.0, (BA + 1) / 256.0)).x), x - 1, y, z - 1)), 
										lerp(u, 
											grad(int(256 * texture2D(permutationVector, vec2( ( (AB + 1) % 16) / 16.0, (AB + 1) / 256.0)).x), x, y - 1, z - 1), 
											grad(int(256 * texture2D(permutationVector, vec2( ( (BB + 1) % 16) / 16.0, (BB + 1) / 256.0)).x), x - 1, y - 1, z - 1))));
	return res;
}

//suma fraktalna szumów
float sum1(float x, float y, float z){
	float t = 0.5;
	float amplitude = 1.0;
	float frequency = 1;
	
	if (x > 0.6*width) {
		t -= 1.3*(25.0 / 4.0) * pow((x - width*0.6), 2) / pow(width, 2);
	}
	else if (x < 0.4f*width) {
		t -= 1.3*(25.0 / 4.0) * pow((width*0.4 - x), 2) / pow(width, 2);
	}
	if (y > 0.6*height) {
		t -= 1.3*(25.0 / 4.0) * pow((y - height*0.6), 2) / pow(height, 2);
	}
	else if (y < 0.4*height) {
		t -= 1.3*(25.0 / 4.0) * pow((height*0.4 - y), 2) / pow(height, 2);
	}

	for (int i = 0; i < octaves; i++) {
		t += noise( ((x*frequency) / zoom), ((y*frequency) / zoom), 0)*amplitude;
		amplitude *= pow(persistence, 3);
		frequency *= pow(2, 4);
	}
	
	if (t < -1.0) {
		t = -1.0;
	}

	if(x > width || x < 0.0 || y > height || y < 0){
		t = 1.0;
	}


	return (t+1)/2.0;
}

//odwracamy wartoœci szumu np 0.3 -> 0.7 0.2-> 0.8 itd.
float invert(float t){
	return abs(t-1);
}

void main() {
	float offset0 = 0.001 + 0.0005*sin(-2*time + (7*gl_FragCoord.x + 2*gl_FragCoord.y)/(resolutionX*resolutionY/1000.0));
;
	float offset1 = 0.005;
	float offset2 = 0.010;
	float offset3 = 0.015;
	float offset4 = 0.020;
	float k = sum1(gl_FragCoord.x + offsetX , gl_FragCoord.y - offsetY, 0);
	float c = abs(noise(gl_FragCoord.x/100.0, gl_FragCoord.y/100.0 ,time));
	vec3 pixel;// = texture2D(texture, vec2((gl_FragCoord.x + offsetX)/resolutionX, (gl_FragCoord.y - offsetY)/resolutionY));
	vec3 deepCol = vec3(0, 0.05, 0.35) * k;
	vec3 shallowCol = vec3(0, 0.6, 0.9) * k;
	vec3 sandCol = vec3(1.0, 0.8, 0.4) * k;
	vec3 grassCol = vec3(0.2, 0.6, 0.1) * k;
	vec3 kk = vec3(k);
	float t;
	float shallowWaterWaves = shallowWater 
							+ 0.0006*sin(time + (2*gl_FragCoord.x + 7*gl_FragCoord.y)/(resolutionX*resolutionY/1000.0))
							+ 0.0006*cos(-0.797*time + (1.3*gl_FragCoord.x + 4.8*gl_FragCoord.y)/(resolutionX*resolutionY/100.0));

	
	
	if ( k < deepWater - offset2){
		pixel = deepCol;
	}
	else if(k < deepWater){
		t = fade((k + offset2 - deepWater)/offset2);
		pixel = lerpV(t, deepCol, shallowCol); 
	}
	else if (k < shallowWater - offset2){
		pixel = shallowCol;
	}
	else if (k < shallowWaterWaves){
		t = fade((k - shallowWater + offset2)/(shallowWaterWaves - shallowWater + offset2));
		pixel = lerpV(t, shallowCol, (1.5*sandCol+shallowCol)/2);
	}
	else if (k < shallowWaterWaves + offset0){
		t = fade((k - shallowWaterWaves)/(offset0));
		pixel = lerpV(t, (1.5*sandCol+shallowCol)/2, (1.7*sandCol+shallowCol)/2);
	}
	else if(k < sand - offset2){
		pixel = sandCol;
	}
	else if(k < sand){
		t = fade((k + offset2 - sand)/offset2);
		pixel = lerpV(t, sandCol, grassCol); 	
	}
	else{
		pixel = grassCol;
	}
	
	gl_FragColor = vec4(pixel, 1.0);
}