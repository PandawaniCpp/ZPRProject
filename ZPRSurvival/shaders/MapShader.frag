uniform sampler2D permutationVector;
uniform float time;
uniform float offsetX;
uniform float offsetY;
uniform float width;
uniform float height;
uniform float zoom;
uniform float persistence;
uniform float octaves;

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
		t -= 1.5*(25.0 / 4.0) * pow((x - width*0.6), 2) / pow(width, 2);
	}
	else if (x < 0.4f*width) {
		t -= 1.5*(25.0 / 4.0) * pow((width*0.4 - x), 2) / pow(width, 2);
	}
	if (y > 0.6*height) {
		t -= 1.5*(25.0 / 4.0) * pow((y - height*0.6), 2) / pow(height, 2);
	}
	else if (y < 0.4*height) {
		t -= 1.5*(25.0 / 4.0) * pow((height*0.4 - y), 2) / pow(height, 2);
	}

	for (int i = 0; i < octaves; i++) {
		t += noise( ((x*frequency) / zoom), ((y*frequency) / zoom), 0)*amplitude;
		amplitude *= persistence;
		frequency *= 2;
	}
	
	if (t < -1.0) {
		t = -1.0;
	}

	if(x>width || x<0.0 || y>height || y<0){
		t = -1.0;
	}


	return t;
}

//Przekszta³cenie z wartoœci -1 do 1 na 0 do 1
float sum11(float t){
	return (t+1)/2.0;
}

//suma fraktalna wartoœci bezwzglêdnych
float sum2(float x, float y, float z){
	float t = 0.0;
	float amplitude = 1.0;
	float frequency = 1;

	for (int i = 0; i < octaves; i++) {
		t += abs(noise( ((x*frequency) / zoom), ((y*frequency) / zoom), z)*amplitude);
		amplitude *= persistence;
		frequency *= 2;
	}

	return t;
}

//mno¿enie kolejnych warstw, jeszcze nie wiem do czego ale zajebista opcja
float sum3(float x, float y, float z){
	float t = 1.0;
	float amplitude = 1.0;
	float frequency = 1;

	for (int i = 0; i < 3; i++) {
		t *= noise((x*frequency) / 100.0, (y*frequency) / 100.0, z);
		amplitude *= 0.5;
		frequency *= 2;
	}

	return t;
}

//odwracamy wartoœci szumu np 0.3 -> 0.7 0.2-> 0.8 itd.
float invert(float t){
	return abs(t-1);
}

void main() {
	float k = invert(sum11(sum1(gl_FragCoord.x + offsetX , gl_FragCoord.y - offsetY, 0)));
	float c = abs(noise(gl_FragCoord.x/100.0, gl_FragCoord.y/100.0 ,time));
	vec4 pixel = vec4(0.0);
    pixel.a = k;
	gl_FragColor = pixel;
}