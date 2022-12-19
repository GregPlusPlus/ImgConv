__kernel void conv2D(const __global uchar *In,
                     __global uchar *Out,
                     __constant float *k) {

    size_t x = get_global_id(0);
    size_t y = get_global_id(1);
    size_t i = (W * y + x) * 3;

    float sumR = 0;
    float sumG = 0;
    float sumB = 0;

    float kv = 0;

    int kRow;
    int px;
    int py;
    int refX = (int)x - (int)(KW / 2);
    int refY = (int)y - (int)(KH / 2);

    for(int yK = 0; yK < KH; yK ++) {
        kRow = KH * yK;

        for(int xK = 0; xK < KW; xK ++) {
            kv = k[kRow + xK];

            px = refX + xK;
            py = refY + yK;

            if(px < 0) {
                px = 0;
            } else if(px >= W) {
                px = W - 1;
            }

            if(py < 0) {
                py = 0;
            } else if(py >= H) {
                py = H - 1;
            }

            int ii = (W * py + px) * 3;

            sumR += kv * In[ii + 0];
            sumG += kv * In[ii + 1];
            sumB += kv * In[ii + 2];
        }
    }

    if(sumR > 255) {
        sumR = 255;
    }

    if(sumG > 255) {
        sumG = 255;
    }

    if(sumB > 255) {
        sumB = 255;
    }

    Out[i + 0] = sumR;
    Out[i + 1] = sumG;
    Out[i + 2] = sumB;
}
