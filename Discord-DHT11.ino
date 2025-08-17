#include <WiFiClientSecure.h>
#include <HTTPClient>
#include <ArduinoJson.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASS";
const char* webhookURL = "https://discord.com/api/webhooks/123/abc";
const char* botToken   = "YOUR_BOT_TOKEN";
const char* channelId  = "YOUR_CHANNEL_ID";

String messageId = "";

WiFiClientSecure client;

// ----------- HTTPS helper -----------
bool discordPost(const String& json, String& outId, bool isEdit = false) {
  HTTPClient https;
  String url = isEdit ? "https://discord.com/api/v10/channels/" + String(channelId) +
                        "/messages/" + messageId
                      : webhookURL;
  https.begin(client, url);
  if (isEdit) https.addHeader("Authorization", "Bot " + String(botToken));
  https.addHeader("Content-Type", "application/json");

  int code = isEdit ? https.PATCH(json) : https.POST(json);
  if (code == HTTP_CODE_OK || code == HTTP_CODE_NO_CONTENT) {
    if (!isEdit) {
      String payload = https.getString();
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      outId = doc["id"].as<String>();
    }
    return true;
  }
  Serial.println("HTTP error " + String(code));
  https.end();
  return false;
}

// ----------- Membuat / update pesan -----------
void updateDiscord(float t, float h) {
  String emoji = (t >= 30) ? "🔥" : (t <= 20) ? "❄️" : "🌡️";
  String json  = "{\"content\":\"📊 **Real-time Monitoring**\\n"
                 "Suhu: `" + String(t, 1) + " °C` " + emoji + "\\n"
                 "Kelembaban: `" + String(h, 1) + " %` \\n"
                 "Diperbarui: <t:" + String(millis()/1000) + ":R>\"}";

  if (messageId == "") {
    if (discordPost(json, messageId, false)) {
      Serial.println("Pesan awal terkirim, id=" + messageId);
    }
  } else {
    String dummy;
    discordPost(json, dummy, true);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  dht.begin();
  client.setInsecure();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal baca DHT11");
    delay(2000);
    return;
  }

  updateDiscord(t, h);

  // Rate-limit Discord (5 detik)
  delay(5000);
}