#include<bits/stdc++.h>
#include "cyklib.hpp"

#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

ll current;

int check(int k) {//czy n > k (return -1), czy n < k (return -2), a jesli akurat zgadnie odp to zwraca n
    int skok = k / 2;
    ll A = current;
    ll B = circular_shift(skok);
    ll C = circular_shift(skok);
    current = C;
    if(A == C)  //okazalo sie ze n = k
            return k;
    int inwersje = 0;
    if(B > C) inwersje++;
    if(A > C) inwersje++;
    if(A > B) inwersje++;
    if(inwersje % 2 == 0)
        return -1;
    else
        return -2;
}

int main() {
	ll x0 = circular_shift(0);
    ll x1 = circular_shift(1);
    if(x0 == x1) {
        give_answer(1);
        return 0;
    }
    x0 = x1;
    x1 = circular_shift(2);
    if(x0 == x1) {
        give_answer(2);
        return 0;
    }
    x0 = x1;
    x1 = circular_shift(3);
    if(x0 == x1) {
        give_answer(3);
        return 0;
    }
    x0 = x1;
    x1 = circular_shift(4);
    if(x0 == x1) {
        give_answer(4);
        return 0;
    }
    current = x1;
    //to bylo sprawdzenie brzegu n <= 4, teraz wiadomo ze n > 4
    ll k = 4;
    while(true) {//ta petla znajduje wstepny zakres, szukamy k takiego że k < n < 2k
        ll res = check(2 * k);
        if(res > 0) {
            give_answer(res);
            return 0;
        }
        if(res == -1)
            k *= 2;
        if(res == -2)
            break;
    }
    //od teraz wiadomo ze k < n < 2k, binsearch
    ll l = k, r = 2 * k, mid;
    while(r - l != 2) {//szukamy n pomiedzy przedzialem otwartym (l,r), jesli trafimy to super, a jesli nie to wtedy l i r beda obok siebie (l + 2 = r), wtedy wynikiem bedzie liczba nieparzysta pomiedzy nimi
        mid = (l + r) / 2;
        ll res = check(mid);
        if(res > 0) {
            give_answer(res);
            return 0;
        }
        if(res == -1)
            l = mid;
        if(res == -2)
            r = mid;
    }
    give_answer(r-1);
	return 0;
}
