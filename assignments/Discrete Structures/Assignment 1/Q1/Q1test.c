#include <stdio.h>

int main(){
	int n, m;
	scanf("%d %d", &n, &m);

	int start[20], end[20]; 
	int used[20] = {0}; 
	int indegree[20] = {0}; 
	int i,j;
	for(i=0 ; i<m ; i++){
		scanf("%d %d", &start[i], &end[i]);
		indegree[end[i]]++;
	}

	for(i=1 ; i<=n ; i++){
		int current;
		for(int j=1 ; j<=n ; j++){
			if(indegree[j] == 0 && used[j] == 0){
				current = j;
				used[j] = 1;
				break;
			}
		}

		for(j=0 ; j<m ; j++){ 			
			if(start[j] == current)
				indegree[end[j]]--;
		}

		printf("%d ", current);
	}
	return 0;
}
