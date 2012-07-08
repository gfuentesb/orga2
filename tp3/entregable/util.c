
char *f = "asdasd";
void exception() {
    static int i = 0;
    int a, b, c, d, e, f;
    a = b = c = d = e = f = 0x12345678; 
    if (i++ < 4) {
        exception();
    } else {
        int i = a;
        void ((*j) (int)) = f;
        j(i);
    /* Invalid opcode por ejecutar un string
       Division Error por dividir por 0
        General Protection Error por hacer un jmp a un segmento inválido */
    }
}
