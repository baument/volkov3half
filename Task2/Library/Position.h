#pragma once
#include <string>

/**
 * @brief Хранит название должности и её необязательное описание.
 */
class Position
{
  private:
    std::string name_;
    std::string description_;

  public:
    /**
     * @brief Создаёт должность с названием и необязательным описанием.
     * @param name Название должности.
     * @param description Описание должности.
     * @throws std::invalid_argument Если название должности пустое.
     */
    Position(const std::string &name, const std::string &description = "");

    /**
     * @brief Возвращает название должности.
     * @return Константная ссылка на название.
     */
    const std::string &getName() const;
    /**
     * @brief Возвращает описание должности.
     * @return Константная ссылка на описание.
     */
    const std::string &getDescription() const;
    /**
     * @brief Возвращает должность в виде одной строки.
     * @return Название или название с описанием.
     */
    std::string toString() const;
};
