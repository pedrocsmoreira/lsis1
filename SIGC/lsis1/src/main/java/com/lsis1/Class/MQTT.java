package com.lsis1.Class;

import io.vertx.core.AsyncResult;
import io.vertx.core.Future;
import io.vertx.core.Handler;
import io.vertx.core.Vertx;
import io.vertx.mqtt.MqttClient;
import io.vertx.mqtt.MqttClientOptions;
import io.vertx.mqtt.messages.MqttConnAckMessage;
import io.vertx.mqtt.messages.MqttPublishMessage;

public class MQTT {
    MqttClient client;
    Vertx vertx;
    Repository repo;

    private final String BROKER_HOST = "maqiatto.com";
    private final int BROKER_PORT = 1883;
    private final String USER_NAME = "email da conta no maqiatto";
    private final String PASSWORD = "palavra-chave da conta no maqiatto";
    private final String topico1 = "topico"; //no maqiatto comecao pelo email
                                             // ex: acs@isep.ipp.pt/lsis1

    public MQTT(Vertx vertx, Repository repo) {
        this.vertx = vertx;
        this.repo = repo;

        MqttClientOptions options = new MqttClientOptions();
        options.setUsername(USER_NAME);
        options.setPassword(PASSWORD);
        client = MqttClient.create(vertx, options);

        Future<MqttConnAckMessage> maqiatto = client.connect(BROKER_PORT, BROKER_HOST);//connectHandler(client));
        maqiatto.onComplete(connectHandler(client));
    }

    private Handler<AsyncResult<MqttConnAckMessage>> connectHandler(MqttClient client) {
        return s -> {
            if(s.succeeded()) {
                System.out.println("ligado e a subscrever topicos " + client.clientId());
                subscrever(topico1);
            }else {
                System.out.println("Falhou ligacao ");
                System.out.println(s.cause());
            }
        };
    }

    public void subscrever(String topico) {
        client.publishHandler(topicHandler()).subscribe(topico, 0);
    }

    private Handler<MqttPublishMessage> topicHandler() {
        return s -> {
            System.out.println("--- Mensagem Nova ---");
            System.out.println("Topico: " + s.topicName());
            System.out.println("Mensagem: " + s.payload().toString());
            System.out.println("QoS: " + s.qosLevel());
            repo.inserirNaBDFalsa(s.payload().toString());
        };
    }
}