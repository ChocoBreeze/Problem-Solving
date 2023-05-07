#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 위, 아래, 앞, 뒤, 왼, 오른쪽
vector<string> U, D, F, B, L, R;
string temp = "___";

void init()
{
    U.assign(3, "www");
    D.assign(3, "yyy");
    F.assign(3, "rrr");
    B.assign(3, "ooo");
    L.assign(3, "ggg");
    R.assign(3, "bbb");
}

/*
(0,0) -> (2,0) / (0,1) -> (1,0) / (0,2) -> (0,0)
(1,0) -> (2,1) / (1,1) -> (1,1) / (1,2) -> (0,1)
(2,0) -> (2,2) / (2,1) -> (1,2) / (2,2) -> (0,2)
*/
void rotateCounterClockWise(vector<string> &strs)
{
    vector<string> copy(begin(strs), end(strs));
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            strs[i][j] = copy[j][2 - i];
        }
    }
}

/*
(0,0) -> (0,2) / (0,1) -> (1,2) / (0,2) -> (2,2)
(1,0) -> (0,1) / (1,1) -> (1,1) / (1,2) -> (2,1)
(2,0) -> (0,0) / (2,1) -> (1,0) / (2,2) -> (2,0)
*/
void rotateClockWise(vector<string> &strs)
{
    vector<string> copy(begin(strs), end(strs));
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            strs[i][j] = copy[2 - j][i];
        }
    }
}

void LeftCounterClockWise()
{ // L-
    temp[0] = U[0][0];
    temp[1] = U[1][0];
    temp[2] = U[2][0];
    U[0][0] = F[0][0];
    U[1][0] = F[1][0];
    U[2][0] = F[2][0];
    F[0][0] = D[0][0];
    F[1][0] = D[1][0];
    F[2][0] = D[2][0];
    D[0][0] = B[0][0];
    D[1][0] = B[1][0];
    D[2][0] = B[2][0];
    B[0][0] = temp[0];
    B[1][0] = temp[1];
    B[2][0] = temp[2];
    // L도 반시계 회전해야 함..
    rotateCounterClockWise(L);
}

void LeftClockWise()
{ // L+
    temp[0] = U[0][0];
    temp[1] = U[1][0];
    temp[2] = U[2][0];
    U[0][0] = B[0][0];
    U[1][0] = B[1][0];
    U[2][0] = B[2][0];
    B[0][0] = D[0][0];
    B[1][0] = D[1][0];
    B[2][0] = D[2][0];
    D[0][0] = F[0][0];
    D[1][0] = F[1][0];
    D[2][0] = F[2][0];
    F[0][0] = temp[0];
    F[1][0] = temp[1];
    F[2][0] = temp[2];
    rotateClockWise(L);
}

void RightCounterClockWise()
{ // R-
    temp[0] = B[0][2];
    temp[1] = B[1][2];
    temp[2] = B[2][2];
    B[0][2] = D[0][2];
    B[1][2] = D[1][2];
    B[2][2] = D[2][2];
    D[0][2] = F[0][2];
    D[1][2] = F[1][2];
    D[2][2] = F[2][2];
    F[0][2] = U[0][2];
    F[1][2] = U[1][2];
    F[2][2] = U[2][2];
    U[0][2] = temp[0];
    U[1][2] = temp[1];
    U[2][2] = temp[2];
    rotateCounterClockWise(R);
}

void RightClockWise()
{ // R+
    temp[0] = B[0][2];
    temp[1] = B[1][2];
    temp[2] = B[2][2];
    B[0][2] = U[0][2];
    B[1][2] = U[1][2];
    B[2][2] = U[2][2];
    U[0][2] = F[0][2];
    U[1][2] = F[1][2];
    U[2][2] = F[2][2];
    F[0][2] = D[0][2];
    F[1][2] = D[1][2];
    F[2][2] = D[2][2];
    D[0][2] = temp[0];
    D[1][2] = temp[1];
    D[2][2] = temp[2];
    rotateClockWise(R);
}

void UpCounterClockWise()
{ // U-
    temp[0] = B[2][0];
    temp[1] = B[2][1];
    temp[2] = B[2][2];
    B[2][0] = R[0][0];
    B[2][1] = R[1][0];
    B[2][2] = R[2][0];
    R[0][0] = F[0][2];
    R[1][0] = F[0][1];
    R[2][0] = F[0][0];
    F[0][2] = L[2][2];
    F[0][1] = L[1][2];
    F[0][0] = L[0][2];
    L[2][2] = temp[0];
    L[1][2] = temp[1];
    L[0][2] = temp[2];
    rotateCounterClockWise(U);
}

void UpClockWise()
{ // U+
    temp[0] = B[2][0];
    temp[1] = B[2][1];
    temp[2] = B[2][2];
    B[2][0] = L[2][2];
    B[2][1] = L[1][2];
    B[2][2] = L[0][2];
    L[2][2] = F[0][2];
    L[1][2] = F[0][1];
    L[0][2] = F[0][0];
    F[0][2] = R[0][0];
    F[0][1] = R[1][0];
    F[0][0] = R[2][0];
    R[0][0] = temp[0];
    R[1][0] = temp[1];
    R[2][0] = temp[2];
    rotateClockWise(U);
}

void DownCounterClockWise()
{ // D-
    temp[0] = F[2][0];
    temp[1] = F[2][1];
    temp[2] = F[2][2];
    F[2][0] = R[2][2];
    F[2][1] = R[1][2];
    F[2][2] = R[0][2];
    R[2][2] = B[0][2];
    R[1][2] = B[0][1];
    R[0][2] = B[0][0];
    B[0][2] = L[0][0];
    B[0][1] = L[1][0];
    B[0][0] = L[2][0];
    L[0][0] = temp[0];
    L[1][0] = temp[1];
    L[2][0] = temp[2];
    rotateCounterClockWise(D);
}

void DownClockWise()
{ // D+
    temp[0] = F[2][0];
    temp[1] = F[2][1];
    temp[2] = F[2][2];
    F[2][0] = L[0][0];
    F[2][1] = L[1][0];
    F[2][2] = L[2][0];
    L[0][0] = B[0][2];
    L[1][0] = B[0][1];
    L[2][0] = B[0][0];
    B[0][2] = R[2][2];
    B[0][1] = R[1][2];
    B[0][0] = R[0][2];
    R[2][2] = temp[0];
    R[1][2] = temp[1];
    R[0][2] = temp[2];
    rotateClockWise(D);
}

void BackCounterClockWise()
{ // B-
    temp[0] = D[2][0];
    temp[1] = D[2][1];
    temp[2] = D[2][2];
    D[2][0] = R[0][2];
    D[2][1] = R[0][1];
    D[2][2] = R[0][0];
    R[0][2] = U[0][2];
    R[0][1] = U[0][1];
    R[0][0] = U[0][0];
    U[0][2] = L[0][2];
    U[0][1] = L[0][1];
    U[0][0] = L[0][0];
    L[0][2] = temp[0];
    L[0][1] = temp[1];
    L[0][0] = temp[2];
    rotateCounterClockWise(B);
}

void BackClockWise()
{ // B+
    temp[0] = D[2][0];
    temp[1] = D[2][1];
    temp[2] = D[2][2];
    D[2][0] = L[0][2];
    D[2][1] = L[0][1];
    D[2][2] = L[0][0];
    L[0][2] = U[0][2];
    L[0][1] = U[0][1];
    L[0][0] = U[0][0];
    U[0][2] = R[0][2];
    U[0][1] = R[0][1];
    U[0][0] = R[0][0];
    R[0][2] = temp[0];
    R[0][1] = temp[1];
    R[0][0] = temp[2];
    rotateClockWise(B);
}

void FrontCounterClockWise()
{ // F-
    temp[0] = U[2][0];
    temp[1] = U[2][1];
    temp[2] = U[2][2];
    U[2][0] = R[2][0];
    U[2][1] = R[2][1];
    U[2][2] = R[2][2];
    R[2][0] = D[0][2];
    R[2][1] = D[0][1];
    R[2][2] = D[0][0];
    D[0][2] = L[2][0];
    D[0][1] = L[2][1];
    D[0][0] = L[2][2];
    L[2][0] = temp[0];
    L[2][1] = temp[1];
    L[2][2] = temp[2];
    rotateCounterClockWise(F);
}

void FrontClockWise()
{ // F+
    temp[0] = U[2][0];
    temp[1] = U[2][1];
    temp[2] = U[2][2];
    U[2][0] = L[2][0];
    U[2][1] = L[2][1];
    U[2][2] = L[2][2];
    L[2][0] = D[0][2];
    L[2][1] = D[0][1];
    L[2][2] = D[0][0];
    D[0][2] = R[2][0];
    D[0][1] = R[2][1];
    D[0][0] = R[2][2];
    R[2][0] = temp[0];
    R[2][1] = temp[1];
    R[2][2] = temp[2];
    rotateClockWise(F);
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int T{};
    cin >> T;

    for (int tc{}; tc < T; ++tc)
    {

        init();
        int N;
        cin >> N;

        for (int n{}; n < N; ++n)
        {
            string op;
            cin >> op;
            if (op == "L-")
                LeftCounterClockWise();
            else if (op == "L+")
                LeftClockWise();
            else if (op == "R-")
                RightCounterClockWise();
            else if (op == "R+")
                RightClockWise();
            else if (op == "F-")
                FrontCounterClockWise();
            else if (op == "F+")
                FrontClockWise();
            else if (op == "B-")
                BackCounterClockWise();
            else if (op == "B+")
                BackClockWise();
            else if (op == "U-")
                UpCounterClockWise();
            else if (op == "U+")
                UpClockWise();
            else if (op == "D-")
                DownCounterClockWise();
            else if (op == "D+")
                DownClockWise();
        }

        // 윗면 출력
        for (string &s : U)
            cout << s << '\n';
    }

    return 0;
}