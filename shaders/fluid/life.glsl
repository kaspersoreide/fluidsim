#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;
uniform vec2 scale;

void main() {
    /*vec4 grid[3][3];
    int neighbours = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = texture(tex, uv + scale * vec2(i - 1, j - 1));
            if (i == 1 && j == 1) continue;
            if (grid[i][j].r == 1.0) neighbours += 1;
        }
    }
    grid[1][1] = texture(tex, uv);*/
    vec4 c = texture(tex, uv);
    c.g += 0.01; 
    FragColor = c;
    //if (result.r == 0.0) {
    //    //dead cell
    //    if (neighbours == 3) result.r = 1.0;
    //} else {
    //    //alive cell
    //    if (neighbours < 2 || neighbours > 3) result.r = 0.0;
    //}
}