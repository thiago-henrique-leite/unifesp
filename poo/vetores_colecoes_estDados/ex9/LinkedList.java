package JavaProjects.vetores_colecoes_estDados.ex9;

public class LinkedList {
	protected No first;
	protected No last;
	protected int length;
	
	public void setFirst(No no) { 
		this.first = no; 
	}
	
	public void setLast(No no) { 
		this.last = no; 
	}
	
	public void setLength(int tam) { 
		this.length = tam;	
	}
	
	public No getFirst() { return first; }
	public No getLast() { return last; }
	public int getLength() { return length; }
	
	public void initiate() {
		setFirst(null); setLast(null); setLength(0);
	}
	
	public boolean isEmpty() {
		return (first == null) ? true : false;
	}
	
	public void addFirst(Object key) {
		No novo = new No(key);
		
		if(isEmpty())
			setLast(novo);
		else
			novo.setNext(first);
		
		setFirst(novo);
		length+=1;
	}
	
	public void addLast(Object key) {
		No novo = new No(key);
		
		if(isEmpty()) {
			first = novo;
			last = novo;
		}
		
		this.last.setNext(novo);
		setLast(novo);
		length+=1;
	}
	
	public void add(Object key, int pos) {
		No novo = new No(key);
		No no = first;
		
		if(pos == 1 || isEmpty())
			addFirst(key);
		else if(pos-1 == length) 
			addLast(key);
		else {
			for(int i=1; i<pos-1; i++)
				no = no.getNext();
			novo.setNext(no.getNext());
			no.setNext(novo);
			length+=1;
		}
	}
	
	public Object removeFirst() {		
		No no = getFirst();
		No origin = no;
		
		if(no == last) { setLast(null); }
		
		setFirst(no.getNext());
		no = null;
		length-=1;
		
		return origin;
	}
	
	public void removeLast() {
		No last = getLast();
		No ant = getFirst();
		
		while(ant.getNext() != last) {
			ant = ant.getNext();
		}
		
		ant.setNext(null);
		setLast(ant);
		last = null;
		length-=1;
	}
	
	public Object remove(Object key) {
		No no = search(key);
		
		if(no==null || isEmpty()) 
			return 0;
		else {
			if(no.equals(this.first))
				removeFirst();
			else if(no.equals(this.last)) 
				removeLast();
			else {
				No ant = this.first;
				while(ant.getNext() != no) {
					ant = ant.getNext();
				}
				ant.setNext(no.getNext());
				no = null;
				length-=1;
			}
			return 1;
		}
	}
	
	public No search(Object key) {
		boolean found=false;
		No no = first;
		
		for(int i=1; i<=length && !found; i++) {
			if(no.getKey() == key)
				found = true;
			else
				no = no.getNext();
		}
		
		if(!found) { return null; }
		else { return no; }
	}
	
	public LinkedList copy_list() {
		LinkedList inverted_list = new LinkedList();
		
		No no = first;
		
		if(no==null || isEmpty()) 
			return null;
		else {
			while(no != this.last.getNext()) {
				inverted_list.addFirst(no.getKey());
				no = no.getNext();
			}
			return inverted_list;
		}
	}
	
	public void print() {
		No no = first;
		System.out.println("");
		while(no != null) {
			no.print();
			no = no.getNext();
			System.out.print(" -> ");
		}
		System.out.println("null");
	}
	
	public boolean validPosition(int pos) {
		return (pos>0 && pos<=this.length+1) ? true : false;	
	}
	
}