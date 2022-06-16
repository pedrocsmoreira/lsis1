package com.lsis1;

import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.Json;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.RoutingContext;
import static io.vertx.ext.web.handler.StaticHandler.DEFAULT_WEB_ROOT;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Date;
import java.util.logging.Logger;

import com.lsis1.Model.Competicao;
import com.lsis1.DAL;

/*
 * 
 * @author Grupo10
 */

public class Handlers {
    String webRoot = DEFAULT_WEB_ROOT;

    public void criarCompeticao(RoutingContext rc) {
        JsonObject body = rc.getBodyAsJson();
        String nome = body.getString("nome");
        String password = body.getString("password");
        Competicao comp = new Competicao(nome, password, new Date());

        DAL.criarCompeticao(comp);

        System.out.println("aluno criado: " + comp.toString());
        rc.response()
                .setStatusCode(201)
                .putHeader("content-type", "application/json; charset=utf-8")
                .end(Json.encodePrettily(comp));
    }

    public void loginCompeticao(RoutingContext rc) {
        JsonObject body = rc.getBodyAsJson();
        String nome = body.getString("nome");
        String password = body.getString("password");
        Competicao comp = rc.getBodyAsJson().mapTo(Competicao.class);

        DAL.loginCompeticao(nome, password);
        
        rc.response()
                .setStatusCode(201)
                .putHeader("content-type","application/json; charset=utf-8")
                .end(Json.encodePrettily(comp));
    }

    public void adicionarDados(RoutingContext rc){
        int numRonda = 0;
        int[] dados = {};
        Competicao comp = rc.getBodyAsJson().mapTo(Competicao.class);

        DAL.adicionarDados(numRonda, dados);
        
        rc.response()
                .setStatusCode(201)
                .putHeader("content-type","application/json; charset=utf-8")
                .end(Json.encodePrettily(comp));
    }
    
}