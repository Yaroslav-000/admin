#ifndef COOKIE_H
#define COOKIE_H

#include <vector>
#include <string>
#include <httplib.h>

using namespace httplib;

struct Cookie {
  /// Название (ключ) cookie
  std::string name = "";
  /// Значение cookie
  std::string value = "";
  /// Устанавливает домен, для которого будет доступен cookie
  std::string domain = "";
  /// Устанавливает путь на сервере, для которого будет доступен cookie
  std::string path = "";
  /// > 0 - устанавливает продолжительность срока действия cookie в секундах; == 0 (по умолчанию) - cookie живут пока не закрыта вкладка; < 0 - удалить немедленно
  int maxAge = 0;
  /// Запрещает доступ к cookie из JavaScript, что помогает предотвратить атаки на кражу сессий
  bool httpOnly = true;
  /// Указывает, что cookie должен быть отправлен только по защищенному (HTTPS) соединению
  bool secure = false;
  /// Указывает, как cookie должен быть отправлен в запросах, связанных с кросс-сайтовыми запросами
  std::string sameSite = SameSiteNoneMode;

  /// Если установлено значение "Strict", cookie не будет отправляться в кросс-сайтовых запросах. Он будет отправляться только в случае, если текущий сайт совпадает с сайтом, на котором установлен cookie
  static const std::string SameSiteStrictMode;
  /// Если установлено значение "Lax", cookie будет отправляться в кросс-сайтовых запросах, если это "безопасный" HTTP-метод, такой как GET, HEAD или OPTIONS, и если это действие инициировано пользователем (например, щелчок по ссылке). Однако, если запрос инициирован из скрипта, cookie не будет отправляться
  static const std::string SameSiteLaxMode;
  /// Если установлено значение "None", cookie будет отправляться во всех кросс-сайтовых запросах. Однако для использования этого значения требуется установка атрибута "Secure", чтобы cookie мог отправляться только по защищенному (HTTPS) соединению
  static const std::string SameSiteNoneMode;

  /// Cookie -> string
  std::string to_string() const;
  /// Формирует HTTP заголовок в котором просит клиент установить cookie и добавляет его в ответ сервера res
  static void set_cookie(Response& res, const Cookie& cookie);
  /// Пытается найти в запросе req куки с именем name. Если таких нет, возвращается пустой объект, если name встречется больше одного раза, то берётся первое которое прислал клиент
  static Cookie get_cookie(const Request& req, const std::string& name);
};

#endif // COOKIE_H