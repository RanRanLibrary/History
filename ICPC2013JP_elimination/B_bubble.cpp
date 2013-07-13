#include <cstdio>
#include <algorithm>

int count[51], pena[51][11], time[51], rank[51];

//比較関数
int cmp( const void* P, const void* Q){
	int p = *(int*)P, q = *(int*)Q;
	if( count[p] < count[q] ||
		count[p] == count[q] && time[p] > time[q] ||
		count[p] == count[q] && time[p] == time[q] && p < q ){
			return 1;
	}
	return -1;
}

int main(){
	int M, T, P, R, m, t, p, j;
	
	while( scanf("%d %d %d %d", &M, &T, &P, &R), M > 0 ){
		//初期化
		std::fill( count, count + 51, 0);
		std::fill( pena[0], pena[0] + 51*11, 0);	//2次元配列の時注意
		std::fill( time, time + 51, 0);
		for(int i=1; i<=T; i++)
			rank[i] = i;
		
		//読み取り
		for(int i=0; i < R; i++){
			scanf("%d %d %d %d", &m, &t, &p, &j);
			if( j == 0 ){
				count[t]++;
				time[t] += pena[t][p] + m;
			}else{
				pena[t][p] += 20;
			}
		}

		//並び替え（バブルソート）
		/*
		bool flag = true;
		while( flag ){	//入れ替えがなくなるまでループ
			flag = false;
			for(int i=1; i < T; i++){
				int p = rank[i], q = rank[i+1];
				//入れ替え
				if( count[p] < count[q] ||
					count[p] == count[q] && time[p] > time[q] ||
					count[p] == count[q] && time[p] == time[q] && p < q ){
						rank[i] = q;
						rank[i+1] = p;
						flag = true;
				}
			}
		}
		*/

		//並び替え（クイックソート）
		qsort( rank+1, T, sizeof(int), cmp );

		//出力
		for(int i=1; i <= T; i++ ){
			printf("%d%c", rank[i], (i==T)?'\n':( count[rank[i]] == count[rank[i+1]] && time[rank[i]] == time[rank[i+1]] )?'=':',' );
		}
		
	}
	
	return 0;
}
