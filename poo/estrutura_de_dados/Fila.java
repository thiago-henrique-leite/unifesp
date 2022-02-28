package JavaProjects.estrutura_de_dados;

public class Fila extends Lista {
	public Fila() {
		super();
	}
	
	public void add(int key) {
		No novo = new No(key);
		
		if(isEmpty())
			setFirst(novo);
		else
			this.last.setNext(novo);
		
		setLast(novo);
		length+=1;
	}
	
	public int remove() {		
		No no = getFirst();
		
		if(isEmpty()) { return 0; }
		
		if(no == last) { setLast(null); }
		
		setFirst(no.getNext());
		no = null;
		length-=1;
		return 1;
	}
}