void exception() {
    static int i = 0;
    int a, b, c, d, e, f;
    a = b = c = d = e = f = 0x12345678; 
    if (i++ < 4) {
        exception();
    } else {
        int i = 0;
        int a = 13 / i;
    }
}
