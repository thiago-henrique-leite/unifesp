package JavaProjects.vetores_colecoes_estDados.ex10;

public class No {
	private Object key;
	private No next;
	
	public No(Object key) {
		setKey(key);
		setNext(null);
	}
	
	public void setKey(Object n) {
		this.key = n;
	}
	
	public void setNext(No no) {
		this.next = no;
	}
	
	public Object getKey() { return key; }
	public No getNext() { return next; }
	
	public void print() {
		System.out.print(key);
	}
}