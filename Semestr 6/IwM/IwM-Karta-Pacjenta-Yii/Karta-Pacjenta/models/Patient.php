<?php

namespace app\models;

use Yii;

/**
 * This is the model class for table "patient".
 *
 * @property int $id
 * @property string $identifier
 * @property string $name
 * @property string $gender
 * @property string $birthDate
 */
class Patient extends \yii\db\ActiveRecord
{
    /**
     * {@inheritdoc}
     */
    public static function tableName()
    {
        return 'patient';
    }

    /**
     * {@inheritdoc}
     */
    public function rules()
    {
        return [
            [['id', 'identifier', 'name', 'gender', 'birthDate'], 'required'],
            [['id'], 'integer'],
            [['identifier', 'name', 'gender', 'birthDate'], 'string'],
            [['id'], 'unique'],
        ];
    }

    /**
     * {@inheritdoc}
     */
    public function attributeLabels()
    {
        return [
            'id' => 'ID',
            'identifier' => 'Identifier',
            'name' => 'Name',
            'gender' => 'Gender',
            'birthDate' => 'Birth Date',
        ];
    }

    // public function getObservations()
    // {
    //     return $this->hasMany(Observation::className(), ['patientIdentifier' => 'identifier']);
    // }

    /**
     * {@inheritdoc}
     * @return PatientQuery the active query used by this AR class.
     */
    public static function find()
    {
        return new PatientQuery(get_called_class());
    }
}
