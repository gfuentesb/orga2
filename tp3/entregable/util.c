void exception() {
    static int i = 0;
    if (i++ < 4) {
        exception();
    } else {
        int i = 0;
        int a = 13 / i;
    }
}
