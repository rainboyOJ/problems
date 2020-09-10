import java.util.*;

class Node extends LinkedList<Node> {
	List<Integer> qs = new LinkedList<Integer>();
	int cnt=0;
	static int[] ans;
	int getAns() {
		for(Node sub: this)
			cnt += sub.getAns();
		for(Integer q: qs)
			ans[q] = cnt;
		return cnt;
	}
}

class Trie {
	Trie[] subs = new Trie[26];
	int w;
	Trie fail, father;
	Node v = new Node();
	Trie(Trie father, int w) {
		this.father = father;
		this.w = w;
	}
	void offer(String s, int k, int q) {
		++v.cnt;
		if(k==s.length()) {
			v.qs.add(q);
			return;
		}
		int c=s.charAt(k)-'a';
		if(subs[c]==null) subs[c]=new Trie(this, c);
		subs[c].offer(s,k+1,q);
	}
	Trie getFail() {
		if(fail!=null) return fail;
		if(father==null||father.getFail()==null)
			return fail=father; 
		fail = father.getFail();
		while(fail.getFail()!=null&&fail.subs[w]==null)
			fail = fail.fail;
		if(fail.subs[w]!=null)
			fail = fail.subs[w];
		return fail;			
	}
	void dfs() {
		for(Trie sub: subs)
			if(sub!=null) sub.dfs();
		if(getFail()!=null)
			fail.v.offer(v);
	}
}

public class Main {
	final static Scanner in = new Scanner(System.in); 
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int N = in.nextInt();
		Trie root = new Trie(null, -1);
		for(int i=0; i<N; ++i)
			root.offer(in.next(), 0, i);
		Node.ans = new int[N];
		root.dfs();
		root.v.getAns();
		for(int x: Node.ans)
			System.out.println(x);
	}

}
