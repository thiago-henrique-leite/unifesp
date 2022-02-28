package JavaProjects.estrutura_de_dados;

public class No {
	private int key;
	private No next;
	
	public No(int key) {
		setKey(key);
		setNext(null);
	}
	
	public void setKey(int n) {
		this.key = n;
	}
	
	public void setNext(No no) {
		this.next = no;
	}
	
	public int getKey() { return key; }
	public No getNext() { return next; }
	
	public void print() {
		System.out.printf("%d", key);
	}
}
