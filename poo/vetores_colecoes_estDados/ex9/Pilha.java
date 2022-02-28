package JavaProjects.vetores_colecoes_estDados.ex9;

//Crie uma classe Pilha com os métodos pop, push e top (retorna o topo da Pilha) a partir de
//uma LinkedList (ou seja, sua classe deve ter um atributo do tipo LinkedList que armaze-
//nará o conteúdo da pilha). Observação: não utilize os métodos pop e push já oferecidos por
//LinkedList; a pilha deve funcionar com objetos de qualquer tipo.

public class Pilha extends LinkedList {	
	public Pilha() {
		super();
	}
	
	public void initiate() {
		setFirst(null); setLength(0);
	}
	
	public void pop(Object key) {
		No novo = new No(key);

		novo.setNext(first);
		setFirst(novo);
		length+=1;
	}
	
	public int push() {		
		No no = getFirst();
		
		if(isEmpty()) { return 0;	}
		
		setFirst(no.getNext());
		no = null;
		length-=1;
		return 1;
	}
	
	public Object top() {
		return getFirst();
	}
	
	public static void main(String args[]) {
		Pilha p = new Pilha();
		
		p.pop(12);
		p.pop("Santos FC");
		p.pop(51.0);
		p.pop("Fabio");
		p.print();
	}
}

