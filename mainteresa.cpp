#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <tuple>

struct Key
{
    int a;
    int b;

    bool operator==(const Key &other) const
    {
        return (a == other.a &&
                b == other.b);
    }
};

template <>
struct std::hash<Key>
{
    std::size_t operator()(const Key &k) const
    {
        using std::hash;
        using std::size_t;

        return k.a ^ (k.b << 1);
    }
};


void solution(int x, int y, std::unordered_map<Key, int> p, std::vector<std::vector<int>> & K)
{

    int max;

    if(K[x][y] != -1){
        return;
    }

    if (!x || !y){
        K[x][y] = 0;
        return;
    }

    max = 0;
    for (int i = 0; i < x/2; i++)
    {
        solution(i, y, p, K); // 1a parte do corte horizontal

        solution(x - i, y, p, K); // 2a parte do corte horizontal

        if (K[i][y] + K[x - i][y] > max)
            max = K[i][y] + K[x - i][y]; // qual e o melhor?? ha corte??
    }

    for (int j = 0; j < y/2; j++)
    { // METADE DO CORTE

        solution(x, j, p, K); // 1a parte corte vertical etc

        solution(x, y -j , p, K);

        if (K[x][j] + K[x][y - j] > max)
            max = K[x][j] + K[x][y - j]; // mm coisa
    }
    if (p.count({x, y})){
        if(p[{x, y}] > max)
            max = p[{x, y}]; // nao ha corte
    
   

    }
    K[x][y] = max;
    return;
}

int main()
{
    int a, b, pi, n, X, Y;
    std::cin >> X >> Y;
    std::cin >> n;
    std::unordered_map<Key, int> p;
    for (int j = 0; j < n; ++j)
    {
        std::cin >> a >> b >> pi;
        p[{a, b}] = pi;
    }

    std::vector<std::vector<int> > K(X + 1, std::vector<int>(Y + 1,0));

    for(int i = 0; i <= X; i++){
        for(int j = 0; j <= Y; j++){
            K[i][j] = -1;
        }
    }
    solution(X, Y, p, K);
    std::cout << K[X][Y];
}