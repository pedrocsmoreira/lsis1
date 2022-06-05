package com.lsis1.Class;

import java.util.Date;

public class Competicao {
    private int id;
    private String nome;
    private Date dataCriacao;

    private static int contador = 0;
    private static final String STR_DEFAULT = "";

    public Competicao(){
        this.id = ++contador;
        this.nome = STR_DEFAULT;
        this.dataCriacao = new Date();
    }

    public Competicao(String nome){
        this.id = ++contador;
        this.nome = nome;
        this.dataCriacao = new Date();
    }

    
    public Competicao(String nome, Date dataCriacao){
        this.id = ++contador;
        this.nome = nome;
        this.dataCriacao = dataCriacao;
    }

}