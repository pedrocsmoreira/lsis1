package com.lsis1.mqtt;


import com.lsis1.controller.controllerMQTT;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AsyncResult;
import io.vertx.core.Future;
import io.vertx.core.Handler;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;
import io.vertx.mqtt.MqttClientOptions;
import io.vertx.mqtt.MqttException;
import io.vertx.mqtt.messages.MqttConnAckMessage;
import io.vertx.mqtt.messages.MqttMessage;
import io.vertx.mqtt.messages.MqttPublishMessage;


public class MQTTCli {
    private final MqttClient client;

    private final Vertx vertx;
    private final String BROKER_HOST = "mq.ttmby.org";
    private final int BROKER_PORT = 1883;
    private final String USER_NAME = "grupo10";
    private final String PASSWORD = "grupo10";
    private final String topico1 = "IGP/LSIS1/Dados";
    private String subtopico = "LSIS1";
    private String subsubtopico = "teste";

    public MQTTCli(Vertx vertx) {
        this.vertx = vertx;
        MqttClientOptions options = new MqttClientOptions();
        options.setUsername(USER_NAME);
        options.setPassword(PASSWORD);
        client = MqttClient.create(vertx, options);
        Future<MqttConnAckMessage> broker = client.connect(BROKER_PORT, BROKER_HOST);
        broker.onComplete(connectHandler(client));
    }

    private Handler<AsyncResult<MqttConnAckMessage>> connectHandler(MqttClient client) {
        return s -> {
            if (s.succeeded()) {
                System.out.println("(MQTT) ligado e a subscrever topicos \\id: " + client.clientId());
                subscrever(topico1);
            } else {
                System.out.println("(MQTT) Falhou ligacao ");
                s.cause();
            }
        };
    }

    public void subscrever(String topico) {
        client.publishHandler(topicHandler()).subscribe(topico, 0);
    }

    public void desinscrever(String topico) {
        client.unsubscribe(topico);
        System.out.println("(MQTT) Desinscrito do topico: " + topico);
    }

    private Handler<MqttPublishMessage> topicHandler() {
        return s -> {
            System.out.println("(MQTT) --- Mensagem Nova ---");
            System.out.println("(MQTT) Topico: " + s.topicName());
            System.out.println("(MQTT) Mensagem: " + s.payload().toString());
            System.out.println("(MQTT) QoS: " + s.qosLevel());
            controllerMQTT controllerMQTT = new controllerMQTT();
            try {
                controllerMQTT.registarBD(s.payload().toString());
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        };
    }

    public String getTopico1() {
        return topico1;
    }

    public String getSubtopico() {
        return subtopico;
    }

    public void setSubtopico(String subtopico) {
        this.subtopico = subtopico;
    }

    public String getSubsubtopico() {
        return subsubtopico;
    }

    public void setSubsubtopico(String subsubtopico) {
        this.subsubtopico = subsubtopico;
    }
}