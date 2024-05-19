// hello world
// unitsize(1cm);
int n = 5; // 正方形的数量
real sideLength = 10; // 正方形的边长
string[] letters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"}; // 每个正方形中间的字母

string a ="wwwbbrwrbrbrrbrbrwrwwrbwrwrrb";
string[] str =array(a);

int gap=10;

path rect = (0, 0)--(sideLength, 0)--(sideLength, sideLength)--(0, sideLength)--cycle;

for (int i = 0; i < length(a); ++i) {
    path t = rect;
    transform x = shift( (i*sideLength +i *gap,0));
    t = x * t;
    filldraw(t,green);
    pair center = (0.5*sideLength ,0.5*sideLength );
    label (str[i],x*center);  
    // label(letters[i], ((i+0.5)*sideLength, sideLength/2));
}

