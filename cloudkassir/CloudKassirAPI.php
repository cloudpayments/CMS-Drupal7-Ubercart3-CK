<?php

if (!class_exists('CloudKassirAPI')) {
    class CloudKassirAPI
    {

        protected $curl = null;

        /**
         * Проверяем айпи адреса с которых пришли запросы
         */
        private function CheckAllowedIps()
        {
            return true;
            // убрали проверку по айпи
            if (!in_array($_SERVER['REMOTE_ADDR'], ['127.0.0.1', '130.193.70.192', '185.98.85.109'])) throw new Exception('CloudKassir: Hacking atempt!');
        }

        /**
         * Проверяем коректность запроса
         */
        private function CheckHMAC($sSercet)
        {
            if (!$sSercet) throw new Exception('CloudKassir: Sercet key is not defined');
            $sPostData = file_get_contents('php://input');
            $sCheckSign = base64_encode(hash_hmac('SHA256', $sPostData, $sSercet, true));
            $sRequestSign = isset($_SERVER['HTTP_CONTENT_HMAC']) ? $_SERVER['HTTP_CONTENT_HMAC'] : '';
            if ($sCheckSign !== $sRequestSign) {
                throw new Exception('CloudKassir: Hacking atempt!');
            };
            return true;
        }


        /**
         * Метод для отправки запросов системе
         * @param string $location
         * @param array $request
         * @return bool|array
         */
        public function MakeRequest($location, $request = array())
        {
            if (!$this->curl) {
                $auth = variable_get('cloudkassir_public_id') . ':' . variable_get('cloudkassir_api_password');
                $this->curl = curl_init();
                curl_setopt($this->curl, CURLOPT_RETURNTRANSFER, true);
                curl_setopt($this->curl, CURLOPT_CONNECTTIMEOUT, 30);
                curl_setopt($this->curl, CURLOPT_TIMEOUT, 30);
                curl_setopt($this->curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
                curl_setopt($this->curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
                curl_setopt($this->curl, CURLOPT_USERPWD, $auth);
            }

            curl_setopt($this->curl, CURLOPT_URL, 'https://api.cloudpayments.ru/' . $location);
            curl_setopt($this->curl, CURLOPT_HTTPHEADER, array(
                "content-type: application/json"
            ));
            curl_setopt($this->curl, CURLOPT_POST, true);
            curl_setopt($this->curl, CURLOPT_POSTFIELDS, json_encode($request));

            $response = curl_exec($this->curl);
            if ($response === false || curl_getinfo($this->curl, CURLINFO_HTTP_CODE) != 200) {
                return false;
            }
            $response = json_decode($response, true);
            if (!isset($response['Success']) || !$response['Success']) {
                drupal_set_message('CloudKassir error: ' . $response['Message'], 'error');
                return false;
            }
            return $response;
        }
    }
}