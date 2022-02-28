package JavaProjects.mortal;

public class Ramo extends Mortal {
	private Ramo left, rigth;
	
	public Ramo() {
		super(null);
		setLeft(null);
		setRigth(null);
	}
	
	public void setLeft(Ramo ramo) {
		this.left = ramo;
	}
	
	public void setRigth(Ramo ramo) {
		this.rigth = ramo;
	}
	
	public boolean ehNo() {
		return (rigth == left && rigth == null) ? true : false;
	}
	
	public int quantFilhos() {
		if(ehNo())
			return 0;
		
		if(rigth != null && left != null)
			return 2 + rigth.quantFilhos() + left.quantFilhos();
		else if(rigth != null) 
			return 1 + rigth.quantFilhos();
		else 
			return 1 + left.quantFilhos();
	}
	
	public Ramo getLeft() { return this.left; }
	public Ramo getRigth() { return this.rigth; }
	
	public void mata() {	
		System.out.printf("\nRamo.mata()");

		setVivo(false);
		if(rigth != null)
			rigth.mata();
		if(left != null)
			left.mata();
	}
	
	public String toString() {
		return this.getClass().getSimpleName() 
				+ " - Quantidade de Filhos: " + this.quantFilhos()
				+ " - Está vivo? " + this.isVivo();
	}
}