__kernel void conv2D(__global uchar *rI, __global uchar *gI, __global uchar *bI,
                     __global uchar *rO, __global uchar *gO, __global uchar *bO,
                     __global float *k,
                     uint w, uint h,
                     uint kw, uint kh) {

    size_t x = get_global_id(0);
    size_t y = get_global_id(1);
    size_t i = w * y + x;

    float sumR = 0;
    float sumG = 0;
    float sumB = 0;

    for(int yK = 0; yK < kh; yK ++) {
        for(int xK = 0; xK < kw; xK ++) {
            float kv = k[kh * yK + xK];

            int px = (int)x - (int)(kw / 2) + (int)xK;
            int py = (int)y - (int)(kh / 2) + (int)yK;

            if(px >= 0 && py >= 0) {
                int ii = w * py + px;

                sumR += kv * (float)rI[ii];
                sumG += kv * (float)gI[ii];
                sumB += kv * (float)bI[ii];
            }
        }
    }

    rO[i] = sumR;
    gO[i] = sumG;
    bO[i] = sumB;
}
