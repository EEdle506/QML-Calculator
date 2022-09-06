#pragma once

#include <QObject>
#include <QMetaEnum>
#include <qqmlregistration.h>

#include <QHash>

#include <QJsonDocument>
#include <QJsonObject>

#include <QJSEngine>

class Standart
    : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString finalValue MEMBER m_FinalValue READ GetFinalValue NOTIFY finalValueChanged)
    QString m_FinalValue;
    Q_PROPERTY(QString prevOperation MEMBER m_FrontJoined READ GetFinalValue NOTIFY finalValueChanged)
    QString m_FrontJoined;

public:
    enum Command {
        del = 0,
        clr,
        clrall,
        equal
    };
    Q_ENUM(Command)

    enum WaitOperation {
        Cmd = 4,
        Function,
        Operator,
        Value,
        Undefined
    };
    Q_FLAG(WaitOperation)
    Q_DECLARE_FLAGS(WaitOperations, WaitOperation)

    struct MathElement
    {
        QString FinalValue;
        QString BackOperation, FrontOperation;

        WaitOperation   LastOperation;
        WaitOperations  LastAvailableOperations;
    };

    Standart(QObject *parent = nullptr);
    ~Standart() override;

    Q_INVOKABLE void processButton(const QString& type, const QString& func, const QString& placeHolder);

    QString GetCalculatedProduct() const;

    const QString& GetPrevOperation() const;
    const QString& GetFinalValue() const;

private: 
	template <typename Enum>
    static Enum ConvertStringToEnum(const QString& en);

	void executeCommand(const QString& cmd);

	void AddValue(const QString& value);
	void AddFunction(const QString& func, const QString& placeHolder);
	void AddOperator(const QString& op);

	void ClearAll();
	void ClearHistory();
	void ClearCalculations();

signals:
    void historyChanged();
    void finalValueChanged();
    void prevValueChanged();

private:
    QJSEngine* m_jsEngine = nullptr;
	QString m_BackJoined;

    QList <MathElement> m_History;

    WaitOperation m_LastOperation;
    WaitOperations m_AvaliableOperations;
};

template <typename Enum>
Enum Standart::ConvertStringToEnum(const QString& enStr)
{
	QMetaEnum en = QMetaEnum::fromType<Enum>();
	if (enStr.isEmpty())
		return static_cast<Enum>(-1);
    return static_cast<Enum>(en.keyToValue(enStr.toUtf8()));
}

Q_DECLARE_OPERATORS_FOR_FLAGS(Standart::WaitOperations)
