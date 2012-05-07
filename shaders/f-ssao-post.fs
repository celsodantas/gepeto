uniform sampler2D realModel;
uniform sampler2D ssaoMap;
uniform sampler2D otherMap;

varying vec2 uv;


void main(void)
{
   
   const float blurSize = 1.0/512.0; // I've chosen this size because this will result in that every step will be one pixel wide if the RTScene texture is of size 512x512
   
   vec4 sum;
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   sum += texture2D(ssaoMap, vec2(uv.x - 4.0*blurSize, uv.y)) * 0.05;
   sum += texture2D(ssaoMap, vec2(uv.x - 3.0*blurSize, uv.y)) * 0.09;
   sum += texture2D(ssaoMap, vec2(uv.x - 2.0*blurSize, uv.y)) * 0.12;
   sum += texture2D(ssaoMap, vec2(uv.x - blurSize, uv.y)) * 0.15;
   sum += texture2D(ssaoMap, vec2(uv.x, uv.y)) * 0.16;
   sum += texture2D(ssaoMap, vec2(uv.x + blurSize, uv.y)) * 0.15;
   sum += texture2D(ssaoMap, vec2(uv.x + 2.0*blurSize, uv.y)) * 0.12;
   sum += texture2D(ssaoMap, vec2(uv.x + 3.0*blurSize, uv.y)) * 0.09;
   sum += texture2D(ssaoMap, vec2(uv.x + 4.0*blurSize, uv.y)) * 0.05;
      
   sum += texture2D(ssaoMap, vec2(uv.x, uv.y - 4.0*blurSize)) * 0.05;
   sum += texture2D(ssaoMap, vec2(uv.x, uv.y - 3.0*blurSize)) * 0.09;
   sum += texture2D(ssaoMap, vec2(uv.x, uv.y - 2.0*blurSize)) * 0.12;
   sum += texture2D(ssaoMap, vec2(uv.x, uv.y - blurSize)) * 0.15;
   sum += texture2D(ssaoMap, vec2(uv.x, uv.y)) * 0.16;
   sum += texture2D(ssaoMap, vec2(uv.x, uv.y + blurSize)) * 0.15;
   sum += texture2D(ssaoMap, vec2(uv.x, uv.y + 2.0*blurSize)) * 0.12;
   sum += texture2D(ssaoMap, vec2(uv.x, uv.y + 3.0*blurSize)) * 0.09;
   sum += texture2D(ssaoMap, vec2(uv.x, uv.y + 4.0*blurSize)) * 0.05;
        
   vec4 currentPixelSample = sum;
   
   currentPixelSample *= 1.0/2.0;
   
   
   vec4 aux = texture2D(realModel, uv);
   aux *= currentPixelSample.r;
   gl_FragColor = aux; 
   
}