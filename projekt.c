#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define SIZE 400

typedef struct{
	char linear[SIZE]; //tu se sprema sve desno od '='
	char var[5]; //ime varijable
	int done; //oznaka jel jednadzba rjesena
	int result;
} equations;

void clean_spaces(char *equation){
/*mice sve viska spaceove koje prebrisavanje uzrokuje*/
	int x = 0;
  	for(int i = 0; equation[i]; ++i){
    	if(!isspace(equation[i]) || (i > 0 && !isspace(equation[i-1]))){
    		equation[x++] = equation[i];
    	}
	}
  	equation[x] = '\0';
}

int check_if_int(char n[]){
/*provjerava jel se radi o broju*/
	for (int i = 0; i < strlen(n); ++i){
		if(isdigit(n[i])){
			continue;
		}
		return 0;
	}
	return 1;
}

int convert(char n[]){
/*pretvara (string)brojeva u (int)broj*/
	int len = strlen(n);
	int number = 0;
	for (int i = 0; i < len; ++i){
		number += ((int)n[i] - 48) * pow(10, len - i - 1);
	}
	return number;
}

int check_which_var(char op[], equations *eq, int n){
/*trazi vrijednost rjesene varijable*/
	for (int i = 0; i < n; ++i){
		if(!strcmp(op, eq[i].var)){
			return eq[i].result;
		}
	}
	return 0;
}

int check_if_var_solved(char op[], equations *eq, int n){
/*provjerava jel varijabla koja se treba koristiti rjesena, odnosno
jel ju smije koristiti prilikom neke operacije*/
	for (int i = 0; i < n; ++i){
		if(!strcmp(op, eq[i].var)){
			if(eq[i].done == 1){
				return 1;
			}
		}
	}
	return 0;
}

int check_if_var(char var[]){
/*provjerava jel se radi o varijabli*/
	for (int i = 0; i < strlen(var); ++i){
		if(isalpha(var[i])){
			return 1;
		}
	}
	return 0;
}

int check_if_punct(char var[]){
/*posto su *, /, + i - stringovi potrebno je provjeriti o kojem se
charu radi, to radi ova funkcija*/ 
	for (int i = 0; i < strlen(var); ++i){
		switch(var[i]){
			case('*'): return 1; break;
			case('/'): return 2; break;
			case('+'): return 3; break;
			case('-'): return 4; break;
		}
	}
	return 0;
}

void sort_by_alph(int n, equations eq[]) { 
/*alfabetsko sortiranje, bubble sort */
	for (int i = 0; i < n ; i++) {
    	for (int j = 1; j < n; j++) {
    		if ((strcmp(eq[j - 1].var, eq[j].var)) > 0) {
        		equations tmp = eq[j - 1];
        		eq[j - 1] = eq[j];
        		eq[j] = tmp;
      		}
    	}
  	}
}

void solve(char *equation, equations *eq, int n, int *res, int *done){
	int offset = 0, n_tmp;
	char tmp[5], operator1[5], operator2[5];
	//u slucaju mnozenja
	while(sscanf(equation + offset, " %[^' '] %n", tmp, &n_tmp) > 0){
		if(check_if_punct(tmp) == 1 || check_if_punct(tmp) == 2){
			int umnt, op1, op2; //umnozak ili kvocijent i operatori
			sscanf(equation + offset + strlen(tmp), " %s", operator2);
			if(check_if_var(operator1)){ //gleda jel varijabla, ako je jel rjesena, ako je koji je rez
				if(check_if_var_solved(operator1, eq, n)){
					op1 = check_which_var(operator1, eq, n);
				}
				else return; //ako nije varijabla rjesena, skip
			}
			else if(check_if_int(operator1)){
				op1 = convert(operator1); //ak je (string)broj onda je (int)broj
			}
			if(check_if_var(operator2)){ //isto tak i za 2. operator
				if(check_if_var_solved(operator2, eq, n)){
					op2 = check_which_var(operator2, eq, n);
				}
				else return;
			}
			else if(check_if_int(operator2)){
				op2 = convert(operator2);
			}

			if(check_if_punct(tmp) == 1) umnt = op1 * op2;
			else if(op2 != 0) umnt = op1 / op2; //mnozenje ili dijeljenje
			char string_umnt[5];
			sprintf(string_umnt, "%d", umnt);
			for (int i = 0; i < strlen(tmp) + strlen(operator1) + strlen(operator2) + 2; ++i){
				*(equation + offset - strlen(operator1) + i - strlen(tmp)) = ' '; 
				/*ovo prebrisuje funkciju mnozenja/dijeljenja s ' ' za svaki znak koje se
				u njoj nalazio, treba ju pocistiti od viska znakova, to radi clean_spaces*/
			}
			strncpy(equation + offset - strlen(operator1) - strlen(tmp), string_umnt, strlen(string_umnt));
			clean_spaces(equation);
			return;
		}
		offset += n_tmp;
		strcpy(operator1, tmp);
	}
	offset = 0;
	//u slucaju zbrajanja/oduzimanja
	while(sscanf(equation + offset, " %s %n", tmp, &n_tmp) > 0){
		if(check_if_punct(tmp) == 3 || check_if_punct(tmp) == 4){
			int zbra, op1, op2;
			sscanf(equation + offset + strlen(tmp), " %s", operator2);
			if(check_if_var(operator1)){ 
				if(check_if_var_solved(operator1, eq, n)){
					op1 = check_which_var(operator1, eq, n);
				}
				else return; 
			}
			else if(check_if_int(operator1)){
				op1 = convert(operator1); 
			}
			if(check_if_var(operator2)){ 
				if(check_if_var_solved(operator2, eq, n)){
					op2 = check_which_var(operator2, eq, n);
				}
				else return;
			}
			else if(check_if_int(operator2)){
				op2 = convert(operator2);
			}
			if(check_if_punct(tmp) == 3) zbra = op1 + op2;
			else zbra = op1 - op2;
			char string_zbra[5];
			sprintf(string_zbra, "%d", zbra);
			for (int i = 0; i < strlen(tmp) + strlen(operator1) + strlen(operator2) + 2; ++i){
				*(equation + offset - strlen(operator1) + i - strlen(tmp)) = ' '; 
			}
			strncpy(equation + offset - strlen(operator1) - strlen(tmp), string_zbra, strlen(string_zbra));
			clean_spaces(equation);
			/*gotovo ista praksa ko i za mnozenje i dijeljenje, minimalne promjene*/
			return;
		}
		offset += n_tmp;
		strcpy(operator1, tmp);
	}
	offset = 0;
	sscanf(equation, " %s", tmp);
	//u slucaju dok je jedna varijabla samo
	if(check_if_var(tmp)){
		if(check_if_var_solved(tmp, eq, n)){
			*res = check_which_var(tmp, eq, n);
			*done = 1;
			return;
		}
		return;
	}
	//ako nije varijabla onda jedino preostaje da bude broj
	if(check_if_int(tmp)){
		*res = convert(tmp);
		*done = 1;
		return;
	}
}

void clean_equation(equations *eq){
/*odvaja ime varijable od njene jednadzbe (ime var) = (jednadzba),
i mice '='*/
	char tmp[5];
	int n_tmp = 0, offset = 0;
	sscanf(eq -> linear, "%s", eq -> var);
	while(sscanf((eq -> linear) + offset, " %s %n", tmp, &n_tmp) > 0){
		offset += n_tmp;

		if(!strcmp(tmp, "=")){
			strcpy(eq -> linear, (eq -> linear) + offset);
			offset = 0;
		}
	} 
}

void get_equation(){
	int num_eq, solved = 0;
	scanf("%d\n", &num_eq);
	equations eq[num_eq];
	for (int i = 0; i < num_eq; ++i){
		fgets(eq[i].linear, SIZE, stdin);
		eq[i].result = 0;
		eq[i].done = 0;
		clean_equation(&eq[i]);
	}
	do{
		for (int i = 0; i < num_eq; ++i){
			if(eq[i].done == 0){
				solve(eq[i].linear, eq, num_eq, &eq[i].result, &eq[i].done);
			}
		}
		solved = 0;
		for (int i = 0; i < num_eq; ++i){
			if(eq[i].done == 1){
				solved++;
			}
		}
	} while(solved < num_eq);

	sort_by_alph(num_eq, eq);
	for (int i = 0; i < num_eq; ++i){
		printf("%s = %d\n", eq[i].var, eq[i].result);
	}
}

int main(){
	int spreadsheet;
	scanf("%d", &spreadsheet);
	for (int i = 0; i < spreadsheet; ++i){
		get_equation();
		printf("\n");
	}
	return 0;
}