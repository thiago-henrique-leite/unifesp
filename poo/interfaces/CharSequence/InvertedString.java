package JavaProjects.interfaces.CharSequence;

import java.util.Scanner;

public class InvertedString implements CharSequence {
	private String str, inverted;
	
	public InvertedString(String str) {
		setString(str);
		setInverted(string_invert(str));
	}

	public void setString(String str) { this.str = str; }
	private void setInverted(String str) { this.inverted = str;	}
	
	public String getString() { return this.str; }
	public String getInverted() { return this.inverted; }
	
	public char charAt(int index) {
		char[] array = inverted.toCharArray();
		
		for(int i=0; i < array.length; i++){
	        if(i == index)
	            return array[index];
	    }
		return '-';
	}

	public int length() {
		String copy = inverted + '\0';
				
	    int count = 0;

	    for (int i = 0; copy.charAt(i) != '\0'; i++) {
	        count++;
	    }

	    return count;
	}

	public CharSequence subSequence(int start, int end) {
		if(start < 0 || start > end || end > inverted.length()) {
			System.err.println("\nValores de início e/ou fim da sub-sequence inválidos.");
			return null;
		}
		else {		
			 return new InvertedString(inverted.substring(start, end));
		}
	}
	
	private String string_invert(String str) {				
		String invert = "";
		
		for(int i = str.length() - 1; i >= 0; i--) {
			invert = invert + str.charAt(i);
		}
		
		return invert;
	}

	public String toString() {
		return getString();
	}
	
	public static void main(String args[]) {
		Scanner read = new Scanner(System.in);
		String user_str;
		
		System.out.print("Insira uma frase: ");
		user_str = read.nextLine();
		
		InvertedString string = new InvertedString(user_str);
		
		System.out.printf("\nString original: %s\n", string.getString());
		
		System.out.printf("\nString invertida: %s\n", string.getInverted());
		
		System.out.printf("\nTamanho da string: %d\n", string.length());
		
		System.out.printf("\nCaracter na posição 3: %c\n", string.charAt(3));
		
		System.out.printf("\nSubSequence (1,4): %s\n", string.subSequence(1, 4));
				
		read.close();
	}
}
