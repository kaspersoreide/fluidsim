#version 430

in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;
//distance between pixels in uv space
uniform vec2 delta;

void main() {
    vec4 grid[3][3];
    int neighbours = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = texture(tex, uv + delta * vec2(i - 1, j - 1));
            if (i == 1 && j == 1) continue;
            if (grid[i][j].r == 1.0) neighbours += 1;
        }
    }

    vec4 c = grid[1][1];
    if (c.r == 0.0) {
        //dead cell
        if (neighbours == 3) c.r = 1.0;
    } else {
        //alive cell
        if (neighbours < 2 || neighbours > 3) c.r = 0.0;
    }
    c.b = neighbours / 8.0;
    FragColor = c;
}