<?php

namespace app\models;

use yii\base\Model;
use yii\data\ActiveDataProvider;
use app\models\Observation;
use kartik\daterange\DateRangeBehavior;

/**
 * ObservationSearch represents the model behind the search form of `app\models\Observation`.
 */
class ObservationSearch extends Observation
{
    public $createTimeRange;
    public $createTimeStart;
    public $createTimeEnd;


    /**
     * {@inheritdoc}
     */
    public function rules()
    {
        return [
            [['id', 'patientIdentifier'], 'integer'],
            [['coding', 'unit', 'date'], 'safe'],
            [['value'], 'number'],
            [['createTimeRange'], 'match', 'pattern' => '/^.+\s\-\s.+$/'],

        ];
    }

    // public function behaviors()
    // {
    //     return [
    //         [
    //             'class' => DateRangeBehavior::className(),
    //             'attribute' => 'createTimeRange',
    //             'dateStartAttribute' => 'createTimeStart',
    //             'dateEndAttribute' => 'createTimeEnd',
    //         ]
    //     ];
    // }

    /**
     * {@inheritdoc}
     */
    public function scenarios()
    {
        // bypass scenarios() implementation in the parent class
        return Model::scenarios();
    }

    /**
     * Creates data provider instance with search query applied
     *
     * @param array $params
     *
     * @return ActiveDataProvider
     */
    public function search($params, $patientIdentifier = null)
    {

        $query = Observation::find()->where(['patientIdentifier' => $patientIdentifier]);

        // add conditions that should always apply here

        $dataProvider = new ActiveDataProvider([
            'query' => $query,
        ]);

        $this->load($params);
        // if (isset($params['createTimeRange'])) {
        // $dates = explode(' - ', '1999-02-24 12:00:00 - 2010-12-03 04:07:00');
        $dates = explode(' - ', $this->createTimeRange);
        if ((bool)strtotime($dates[0]) && (bool)strtotime($dates[1])) {
            $this->createTimeStart = $dates[0];
            $this->createTimeEnd = $dates[1];
        }
        // }

        if (!$this->validate()) {
            // uncomment the following line if you do not want to return any records when validation fails
            $query->where('0=1');
            return $dataProvider;
        }

        // grid filtering conditions
        $query->andFilterWhere([
            'id' => $this->id,
            'value' => $this->value,
            'patientIdentifier' => $this->patientIdentifier,
        ]);

        $query->andFilterWhere(['like', 'coding', $this->coding])
            ->andFilterWhere(['like', 'unit', $this->unit])
            ->andFilterWhere(['>=', 'date', $this->createTimeStart])
            ->andFilterWhere(['<=', 'date', $this->createTimeEnd]);
        // ->andFilterWhere(['date' => $this->date]);

        return $dataProvider;
    }
}
