package JavaProjects.estrutura_de_dados;

public class Pilha extends Lista {
	public Pilha() {
		super();
	}
	
	public void initiate() {
		setFirst(null); setLength(0);
	}
	
	public void add(int key) {
		No novo = new No(key);

		novo.setNext(first);
		setFirst(novo);
		length+=1;
	}
	
	public int remove() {		
		No no = getFirst();
		
		if(isEmpty()) { return 0;	}
		
		setFirst(no.getNext());
		no = null;
		length-=1;
		return 1;
	}
}
