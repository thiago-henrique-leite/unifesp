package JavaProjects.vetores_colecoes_estDados.ex10;

//Crie uma classe Fila com os métodos enfileira, desenfileira e vazio (verifica se a fila está vazia) a
//partir de uma LinkedList. A fila deve funcionar com objetos de qualquer tipo.

public class Fila extends LinkedList {
	public Fila() {
		super();
	}
	
	public void add(Object key) {
		No novo = new No(key);
		
		if(isEmpty())
			setFirst(novo);
		else
			this.last.setNext(novo);
		
		setLast(novo);
		length+=1;
	}
	
	public Object remove() {		
		No no = getFirst();
		
		if(isEmpty()) { return 0; }
		
		if(no == last) { setLast(null); }
		
		setFirst(no.getNext());
		no = null;
		length-=1;
		return 1;
	}
	
	public boolean isEmpty() {
		return (first == null) ? true : false;
	}
	
	public static void main(String args[]) {
		Fila fila = new Fila();
		
		fila.add("String");
		fila.add(12);
		fila.add(78.6);
		fila.add("Java é brabo");
		
		fila.remove();
		
		System.out.printf("Fila é vazia? %s", fila.isEmpty());
		fila.print();
	}
}