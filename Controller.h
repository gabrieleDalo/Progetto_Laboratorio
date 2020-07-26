/**
 * @author Gabriele D'Alò
 * @version 06/07/2020
 */

#ifndef PROGETTO_LABORATORIO_CONTROLLER_H
#define PROGETTO_LABORATORIO_CONTROLLER_H

#include "Model.h"

class Controller {
public:
    explicit Controller(Model* m,bool error = false) : model(m),error(error) {}

    Controller(){}

    virtual ~Controller(){
        delete model;
    }

    void checkCell(int x,int y,string row,string column,string data);

    void checkOperation(int x,int y,string row,string column,string data);

    float checkString(string data);

    float checkFormula(int row,int column,string data);

    int convertLabelValue(string value);

    vector<float> getRange(int currentRow,int currentColumn,string data);

    bool isError() const;

    void setError(bool error);

    Model *getModel() const;

    void setModel(Model *model);

private:
    Model* model;
    bool error;
};


#endif //PROGETTO_LABORATORIO_CONTROLLER_H
