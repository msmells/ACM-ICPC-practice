#include <iostream>
#include <stack>

using namespace std;

long long abbs(long long i){
	if(i < 0) return -1*i;
	else return i;
}

struct contFrac{
	stack<long long> nums;
};

struct normFrac{
	long long n;
	long long d;
};

normFrac toNorm(contFrac t){
	normFrac ans;
	if(t.nums.size() == 1){
		ans.n = t.nums.top();
		ans.d = 1;
		return ans;
	}
	long long curr;
	ans.n = t.nums.top();
	t.nums.pop();
	ans.d = t.nums.top() * ans.n + 1;
	t.nums.pop();
	while(!t.nums.empty()){
		curr = ans.n;
		ans.n = ans.d;
		ans.d = curr + ans.n * t.nums.top();
		t.nums.pop();
	}
	curr = ans.n;
	ans.n = ans.d;
	ans.d = curr;
	
	return ans;
}

contFrac toCont(normFrac t){
	contFrac ans;
	long long curr;
	if(t.n == t.d){
		ans.nums.push(1);
		return ans;
	}
	while(t.n != 1 && t.d != 0){
		if(t.n >= 0){
			ans.nums.push(t.n / t.d);
			t.n = t.n % t.d;
		}
		curr = t.n;
		t.n = t.d;
		t.d = curr;
	}
	if(ans.nums.empty() && t.d != -1) ans.nums.push(0);
	if(t.n == 1 && t.d != 0) ans.nums.push(t.d);
	return ans;
}

contFrac toContNeg(normFrac t){ //ELIMINATE THIS FUNCTION
}

normFrac add(normFrac an, normFrac bn){
	normFrac res;
	res.n = an.n*bn.d + bn.n*an.d;
	res.d = an.d*bn.d;
	return res;
}

normFrac sub(normFrac an, normFrac bn){
	normFrac res;
	res.n = an.n*bn.d - bn.n*an.d;
	res.d = an.d*bn.d;
	return res;
}

normFrac mul(normFrac an, normFrac bn){
	normFrac res;
	res.n = an.n*bn.n;
	res.d = an.d*bn.d;
	return res;
}

normFrac div(normFrac an, normFrac bn){
	normFrac res;
	res.n = an.n*bn.d;
	res.d = an.d*bn.n;
	return res;
}

int main(){
	long long numa, numb;
	cin >> numa >> numb;
	int casa = 0;
	while(numa != 0 || numb != 0){
		#ifdef DEBUG
			cout << endl << endl;
		#endif
		
		casa++;
		cout << "Case " << casa << ": " << endl;
		
		contFrac ac, bc;
		long long thisa, thisb;
		
		for(long long i = 0; i < numa; i++){
			cin >> thisa;
			ac.nums.push(thisa);
		}
		for(long long i = 0; i < numb; i++){
			cin >> thisb;
			bc.nums.push(thisb);
		}
		
		normFrac an = toNorm(ac);
		normFrac bn = toNorm(bc);
		
		#ifdef DEBUG 
			cout << "an:\t" << an.n << "\t/ " << an.d << endl;
			cout << "bn:\t" << bn.n << "\t/ " << bn.d << endl;
		#endif
		
		normFrac ran = add(an, bn);
		normFrac rsn = sub(an, bn);
		normFrac rmn = mul(an, bn);
		normFrac rdn = div(an, bn);
		
		#ifdef DEBUG
			cout << "ran:\t" << ran.n << "\t/ " << ran.d << endl;
			cout << "rsn:\t" << rsn.n << "\t/ " << rsn.d << endl;
			cout << "rmn:\t" << rmn.n << "\t/ " << rmn.d << endl;
			cout << "rdn:\t" << rdn.n << "\t/ " << rdn.d << endl;
		#endif
		
		contFrac rac = toCont(ran);
		contFrac rsc = toCont(rsn);
		contFrac rmc = toCont(rmn);
		contFrac rdc = toCont(rdn);
		
		stack<long long> a, s, m, d;
		while(!rac.nums.empty()){
			a.push(rac.nums.top());
			rac.nums.pop();
		}
		while(!rsc.nums.empty()){
			s.push(rsc.nums.top());
			rsc.nums.pop();
		}
		while(!rmc.nums.empty()){
			m.push(rmc.nums.top());
			rmc.nums.pop();
		}
		while(!rdc.nums.empty()){
			d.push(rdc.nums.top());
			rdc.nums.pop();
		}		
					
		#ifdef DEBUG
			cout << endl;
		#endif
		
		while(!a.empty()){
			cout << a.top() << " ";
			a.pop();
		} cout << endl;
		while(!s.empty()){
			cout << s.top() << " ";
			s.pop();
		} cout << endl;
		while(!m.empty()){
			cout << m.top() << " ";
			m.pop();
		} cout << endl;
		while(!d.empty()){
			cout << d.top() << " ";
			d.pop();
		} cout << endl;

		cin >> numa >> numb;
	}
	
	return 0;
}
