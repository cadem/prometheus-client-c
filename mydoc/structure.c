struct prom_collector_registry {
  const char *name;
  bool disable_process_metrics;              /**< Disables the collection of process metrics */
  prom_map_t *collectors;                    /**< Map of collectors keyed by name */
  prom_string_builder_t *string_builder;     /**< Enables string building */
  prom_metric_formatter_t *metric_formatter; /**< metric formatter for metric exposition on bridge call */
  pthread_rwlock_t *lock;                    /**< mutex for safety against concurrent registration */
};

struct prom_collector {
  const char *name;
  prom_map_t *metrics;
  prom_collect_fn *collect_fn;
  prom_string_builder_t *string_builder;
  const char *proc_limits_file_path;
  const char *proc_stat_file_path;
};

typedef enum prom_metric_type { PROM_COUNTER, PROM_GAUGE, PROM_HISTOGRAM, PROM_SUMMARY } prom_metric_type_t;

struct prom_metric {
  prom_metric_type_t type;            /**< metric_type      The type of metric */
  const char *name;                   /**< name             The name of the metric */
  const char *help;                   /**< help             The help output for the metric */
  prom_map_t *samples;                /**< samples          Map comprised of samples for the given metric */
  prom_histogram_buckets_t *buckets;  /**< buckets          Array of histogram bucket upper bound values */
  size_t label_key_count;             /**< label_keys_count The count of labe_keys*/
  prom_metric_formatter_t *formatter; /**< formatter        The metric formatter  */
  pthread_rwlock_t *rwlock;           /**< rwlock           Required for locking on certain non-atomic operations */
  const char **label_keys;            /**< labels           Array comprised of const char **/
};


struct prom_metric_sample {
  prom_metric_type_t type; /**< type is the metric type for the sample */
  char *l_value;           /**< l_value is the full metric name and label set represeted as a string */
  _Atomic double r_value;  /**< r_value is the value of the metric sample */
};