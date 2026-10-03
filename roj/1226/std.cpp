// ROJ 1226 装箱问题（同 POJ 1017）
// 题面：6*6*h 的箱子，装高度同为 h 的 1*1 ~ 6*6 六种产品，求最少箱数。
//
// 贪心策略（按大件优先）：
//   6*6：每件独占一箱；
//   5*5：每件独占一箱，剩 11 格；
//   4*4：每件独占一箱，剩 20 格；
//   3*3：每 4 件正好拼满一箱；
//   2*2：先填 5*5、4*4、3*3 整箱里的剩余空位，放不下再开新箱（每箱 9 件）；
//   1*1：填所有箱子里的剩余空位，放不下再开新箱（每箱 36 件）。
// 输入多行订单，每行六个整数（1*1 到 6*6 的数量），以 6 个 0 结尾；
// 每个订单输出一个最少箱数。
#include <cstdio>

// 一个整箱里剩余的 3*3 件数为 k（k = three % 4）时，还能塞下的 2*2 件数
// k = 0：该箱 4 件 3*3 已满；k = 1/2/3：分别还能放 5/3/1 件 2*2
static const int TWO_LEFT[4] = {0, 5, 3, 1};

int main() {
    int one, two, three, four, five, six;
    while (scanf("%d%d%d%d%d%d", &one, &two, &three, &four, &five, &six) == 6) {
        if (one + two + three + four + five + six == 0)
            break;

        // 6*6、5*5、4*4 各占整箱；3*3 每 4 件拼满一箱
        int box = six + five + four + (three + 3) / 4;

        // 2*2 可用的现成空位：每件 4*4 余 5 个，每个 3*3 整箱余 TWO_LEFT 个
        int slot2 = 5 * four + TWO_LEFT[three % 4];
        if (two > slot2)
            box += (two - slot2 + 8) / 9;  // 新开的箱每箱装 9 件 2*2

        // 1*1 可用格子 = 全部箱子总格子 - 其它产品占掉的格子
        // （5*5 占 25 格、4*4 占 16 格、3*3 占 9 格、2*2 占 4 格、6*6 占满 36 格）
        int cell = 36 * box - 36 * six - 25 * five - 16 * four - 9 * three - 4 * two;
        if (one > cell)
            box += (one - cell + 35) / 36;  // 新开的箱每箱装 36 件 1*1

        printf("%d\n", box);
    }
    return 0;
}
